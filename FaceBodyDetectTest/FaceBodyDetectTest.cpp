/**
 * Test adaptive person identification by feeding all images under given directory
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

#include <sys/types.h>
#include <dirent.h>

#include <adaptive_person_id.h>
#include <face_identification.h>
#include <human_detection.h>
#include <body_identification.h>
#include "image_draw.h"

using namespace std;

vector<string> get_file_list(const string& path) {
	vector<string> result;

	DIR* dp = opendir(path.c_str());
	if (dp == nullptr) {
		printf("fail to opendir '%s'. error: %s\n", path.c_str(), strerror(errno));
		return result;
	}

	struct dirent* ep;
	while ((ep = readdir(dp)) != nullptr) {
		// skip directory "." and ".."
		if ((strcmp(ep->d_name, ".") != 0) && (strcmp(ep->d_name, "..") != 0)) {
			result.push_back(path + "/" + ep->d_name);
		}
	}
	closedir(dp);

	sort(result.begin(), result.end());

	return result;
}

bool parse_args(int argc, char** argv, string& model_dir, string& data_dir, string& image_dir,
	int& play_interval, int& loop_cnt, bool& step, bool& inputType) {

	//////////
	// Arguments:
	// 1. mandatory argumenets:
	//    model_dir: top directory to all trained models
	//    data_dir:  top direcotry to save face and body data
	//    -image_dir/video_dir: directory to test images
	// 2. optional arguments:
	//    -i: interval (in milliseconds) to play next image, defaults to 33 ms
	//    -l: the number to loop over all input images
	//    -s: play each image in "single step" mode
	/////////
	if (argc < 4) {
		cout << "Usage: FacebodyDetectTest <model_dir> <data_dir> <-identify> <usb port('0')> [-i ii] [-l ll] [-s]" << endl;
		cout << "Usage: FacebodyDetectTest <model_dir> <data_dir> <-register> <image dir> <person name> [-i ii] [-l ll] [-s]" << endl;
		return false;
	}

	model_dir = argv[1];
	data_dir = argv[2];

	if (argc > 4) {
		if (strcmp(argv[3], "-register") == 0) {
			image_dir = argv[4];
			inputType = false;
		}
		else if (strcmp(argv[3], "-identify") == 0) {
			image_dir = argv[4];
			inputType = true;
		}
		else {
			cout << "Wrong Input type selection.  " << argc << endl;
			return false;
		}
	}
	else {
		cout << "Not enough input argument for registering/Identifying Image/Video." << endl;
		return false;
	}

	play_interval = 33;   // 30 fps
	loop_cnt = 0;
	step = false;
	if (argc > 5) {
		int i = 5;
		while (i < argc) {
			if (strcmp(argv[5], "-i") == 0) {
				i++;
				if (i >= argc) {
					cout << "missing value for option '-i'" << endl;
					return false;
				}
				play_interval = atoi(argv[i]);
			}
			else if (strcmp(argv[5], "-l") == 0) {
				i++;
				if (i >= argc) {
					cout << "missing value for option '-l'" << endl;
					return false;
				}
				loop_cnt = atoi(argv[i]);
			}
			else if (strcmp(argv[5], "-s") == 0) {
				step = true;
			}
			++i;
		}
	}

	return true;
}

int main(int argc, char** argv) {

	string model_dir, data_dir, image_dir, name;
	int interval_ms, loop_cnt;
	bool step, inputType;
	if (!parse_args(argc, argv, model_dir, data_dir, image_dir, interval_ms, loop_cnt, step, inputType))
		return false;

	interval_ms = 33;   // 33 ms for 30 fps
	loop_cnt = 0;
	step = false;

	if (inputType == 0) {
		if (argc >= 5 && argv[5] != "\0") {
			name = (argv[5]);
			cout << "Register person name :" << name << std::endl;
		}
		else {
			cout << "Registration person name is missing." << std::endl;
			return false;
		}
	}
	//inputType = true;
	//  name = "Vishnu";

	//string model_dir = string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Models");
	//string data_dir = string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Models");
	//string image_dir = string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Images");
	//string image_dir = string("0");

	cout << "model dir: " << model_dir << endl;
	cout << "data dir: " << data_dir << endl;
	cout << "image dir: " << image_dir << endl;
	cout << "play interval: " << interval_ms << " ms" << endl;
	cout << "play count: " << loop_cnt << endl;
	cout << "step: " << step << endl;


	string ssd_model = model_dir + "/ssd/openvino_fp32.xml";
	string ssd_device("CPU");
	string body_id_model = model_dir + "/body/aligned_reid_openvino_fp32.xml";
	string body_id_device("CPU");
	string body_feature_path = data_dir + "/body/kdtree";
	int body_feature_dim = 2048;
	string face_det_model = model_dir + "/face/retinaface/faceDetector_fp32.xml";
	string face_det_device("CPU");
	string face_feature_model = model_dir + "/face/arcface50/openvino_fp32.xml";
	string face_feature_device("CPU");
	int face_feature_dim = 512;
	string face_feature_path = data_dir + "/face";


	vector<string> image_files;
	cv::VideoCapture capture;
	cv::Mat image;
	size_t frame_count = 0;
	AdaptivePersonId person_id;

	if (inputType) {
		/*if (image_dir.length() >= 3)
			capture.open(image_dir.c_str());			// offline - filepath
		else*/
		capture.open(atoi(image_dir.c_str()));		// live-video - cameraID (0)
		if (!capture.isOpened()) {
			cout << "Error opening video stream or file" << endl;
			return -1;
		}


		HumanDetection human_det(ssd_model, ssd_device);
		BodyIdentification body_identify(body_id_model, body_id_device, body_feature_dim, body_feature_path);
		auto face_detect = make_shared<FaceDetection>(face_det_model, face_det_device);
		auto face_fature_extract = make_shared<FaceFeatureExtraction>(face_feature_model, face_feature_device, face_feature_dim);
		auto face_id = make_shared<FaceIdentification>(face_feature_path, face_detect, face_fature_extract);


		if (atoi(argv[5]) == 1)
		{
			bool succ = person_id.initialize(ssd_model, ssd_device,
				body_id_model, body_id_device, body_feature_dim, body_feature_path,
				face_det_model, face_det_device, face_feature_model, face_feature_device, face_feature_dim,
				face_feature_path, AdaptivePersonId::Mode::Identify);
			if (!succ) return -1;
		}
		else if (atoi(argv[5]) == 2)
		{
			if (!human_det.initialize()) {
				return false;
			}
		}
		else if (atoi(argv[5]) == 3)
		{
			if (!human_det.initialize()) {
				return false;
			}

			if (!body_identify.initialize()) return false;
		}
		else if (atoi(argv[5]) == 4)
		{
			if (!human_det.initialize()) {
				return false;
			}

			if (!face_id->initialize()) return false;
		}
		else if (atoi(argv[5]) == 5)
		{
			if (!face_detect->initialize()) return false;
		}


		while (true) {
			capture.read(image);
			if (atoi(argv[5]) == 1)
			{
				auto result = person_id.identify(image);
				person_id.draw_images();
			}
			else if (atoi(argv[5]) == 2)
			{
				cv::Mat image_for_drawn;

				PersonIdMsg human_msg = human_det.detect(image, 5);
				image.copyTo(image_for_drawn);
				for (size_t j = 0; j < human_msg.persons_size(); j++)
				{
					Person* result = human_msg.mutable_persons(j);
					cv::Rect face_rect(result->x(), result->y(), result->w(), result->h());
					drawBBox(image_for_drawn, "  ", face_rect, cv::Scalar(0, 255, 0));
					cv::namedWindow("Human Detection", cv::WINDOW_NORMAL);
					cv::imshow("Human Detection", image_for_drawn);
					//cv::waitKey(0);
				}
			}
			else if (atoi(argv[5]) == 3)
			{
				cv::Mat image_for_drawn;

				PersonIdMsg humandetect_msg = human_det.detect(image, 10);
				for (size_t j = 0; j < humandetect_msg.persons_size(); j++)
				{
					humandetect_msg.mutable_persons(j)->set_source(NEED_RECOG);
				}
				PersonIdMsg human_msg = body_identify.identify(humandetect_msg);
				cv::Mat face_id_image = body_identify.get_drawn_image();
				cv::namedWindow("Body identification", cv::WINDOW_NORMAL);
				cv::imshow("Body identification", face_id_image);
			}
			else if (atoi(argv[5]) == 4)
			{
				cv::Mat image_for_drawn;

				PersonIdMsg humandetect_msg = human_det.detect(image, 10);
				for (size_t j = 0; j < humandetect_msg.persons_size(); j++)
				{
					humandetect_msg.mutable_persons(j)->set_source(NEED_RECOG);
				}
				PersonIdMsg face_msg = face_id->identify(humandetect_msg);
				cv::Mat face_id_image = face_id->get_drawn_image();
				cv::namedWindow("Face identification", cv::WINDOW_NORMAL);
				cv::imshow("Face identification", face_id_image);
				/*image.copyTo(image_for_drawn);
				for (size_t j = 0; j < face_msg.persons_size(); j++)
				{
					Person* result = face_msg.mutable_persons(j);
					cv::Rect face_rect(result->x(), result->y(), result->w(), result->h());
					drawBBox(image_for_drawn, result->name(), face_rect, cv::Scalar(0, 255, 0));
					Person* result1 = humandetect_msg.mutable_persons(j);
					cv::Rect face_rect1(result1->x(), result1->y(), result1->w(), result1->h());
					drawBBox(image_for_drawn, result1->name(), face_rect1, cv::Scalar(0, 0, 0));

					cv::waitKey(0);
				}*/
			}
			else if (atoi(argv[5]) == 5)
			{
				std::vector< bbox > result;
				cv::Mat image_for_drawn;
				face_detect->detect(image, result);
				image.copyTo(image_for_drawn);
				for (size_t j = 0; j < result.size(); j++)
				{
					cv::Rect face_rect(result[j].x1, result[j].y1, result[j].x2 - result[j].x1, result[j].y2 - result[j].y1);
					drawBBox(image_for_drawn, "  ", face_rect, cv::Scalar(0, 255, 0));
					cv::namedWindow("Face Detection", cv::WINDOW_NORMAL);
					cv::imshow("Face Detection", image_for_drawn);
				}
			}

			this_thread::sleep_for(chrono::milliseconds(interval_ms));
			char c = cv::waitKey(1);
			if (c == 'q' || c == 'Q')
			{
				break;
			}
		}
		capture.release();
		cv::destroyAllWindows();

	}
	else {
		image_files = get_file_list(image_dir);
		bool succ = person_id.initialize(ssd_model, ssd_device,
			body_id_model, body_id_device, body_feature_dim, body_feature_path,
			face_det_model, face_det_device, face_feature_model, face_feature_device, face_feature_dim,
			face_feature_path, AdaptivePersonId::Mode::Register);
		if (!succ) return -1;

		for (auto& file : image_files) {
			cv::Mat image = cv::imread(file, cv::IMREAD_COLOR);
			if (image.empty()) {
				cout << "fail to read image file: " << file << endl;
				break;
			}

			bool succ = person_id.register_person(image, name);
			person_id.draw_images();

			if (!succ) {
				cout << "fail to register using file: " << file << endl;
			}

			this_thread::sleep_for(chrono::milliseconds(interval_ms));
			char c = cv::waitKey(1);
			if (c == 'q' || c == 'Q')
			{
				break;
			}
		}
		cv::destroyAllWindows();
	}


	// for (auto& p : result.persons()) {
	//   printf("image: %s\nPerson: name(%s), fused(%d), source(%d), face(%d)\n", file.c_str(), p.name().c_str(), p.fused(), p.source(), p.face_from_detection());
	// }

/*if (step) {
	char s;
	cin >> s;
}
else {
	this_thread::sleep_for(chrono::milliseconds(interval_ms));
}*/


//loop_cnt--;
//if (loop_cnt <= 0) break;
	return 0;
}
