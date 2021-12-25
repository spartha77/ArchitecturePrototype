using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ManagedCommandsWrapper;
using System.IO;

//delegate void UpdateAdaptiveHumanTrackingFormDelegate(Bitmap image);
namespace HumanDetectionAndTracking
{
    public partial class AdaptiveHumanTrackingForm : Form
    {
        private Bitmap m_image;
        //ManagedCommandsWrapper.MngdRegisterPersonCommand m_ManagedRegisterPersonCommand;
        //ManagedCommandsWrapper.MngdOpenCVWrapper m_OpenCvWrapper;
        //private System.ComponentModel.BackgroundWorker backgroundWorker1;

        public AdaptiveHumanTrackingForm()
        {
            InitializeComponent();

            //m_ManagedRegisterPersonCommand = new ManagedCommandsWrapper.MngdRegisterPersonCommand();
            //UpdateAdaptiveHumanTrackingFormDelegate updateAdaptiveTrackingFormDelegate =
            //    new UpdateAdaptiveHumanTrackingFormDelegate(UpdateImage);

            // Set the delegate with the call back method
            //m_ManagedRegisterPersonCommand.SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateImage);

            //InitializeBackgroundWorker();
        }
        //private void InitializeBackgroundWorker()
        //{
        //    //this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
        //    //backgroundWorker1.DoWork +=
        //       // new DoWorkEventHandler(backgroundWorker1_DoWork);
        //    //backgroundWorker1.RunWorkerCompleted +=
        //    //    new RunWorkerCompletedEventHandler(
        //    //backgroundWorker1_RunWorkerCompleted);
        //    //backgroundWorker1.ProgressChanged +=
        //    //    new ProgressChangedEventHandler(
        //    //backgroundWorker1_ProgressChanged);
        //}
        // This event handler is where the actual,
        // potentially time-consuming work is done.
        //private void backgroundWorker1_DoWork(object sender,
        //    DoWorkEventArgs e)
        //{
        //    // Get the BackgroundWorker that raised this event.
        //    BackgroundWorker worker = sender as BackgroundWorker;

        //    // Assign the result of the computation
        //    // to the Result property of the DoWorkEventArgs
        //    // object. This is will be available to the 
        //    // RunWorkerCompleted eventhandler.
        //    //e.Result = ComputeFibonacci((int)e.Argument, worker, e);
        //    m_OpenCvWrapper.TriggerUpdate();
        //    e.Result = 0;
        //}
        //private ImageSource ConvertBitmapToImageSource(Bitmap imToConvert)
        //{
        //    Bitmap bmp = new Bitmap(imToConvert);
        //    MemoryStream ms = new MemoryStream();
        //    bmp.Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);

        //    BitmapImage image = new BitmapImage();
        //    image.BeginInit();
        //    ms.Seek(0, SeekOrigin.Begin);
        //    image.StreamSource = ms;
        //    image.EndInit();

        //    ImageSource sc = (ImageSource)image;

        //    return sc;
        //}
        private void AdaptiveHumanTrackingForm_Load(object sender, EventArgs e)
        {
            //SetImage();
        }
        //private void SetImage()
        //{
        //    m_image = m_OpenCvWrapper.GetBitMap();
        //    OpenCVPictureBox.Image = m_image;
        //    this.Refresh();
        //}
        //public static void InvokeIfRequired<T>(this T c, Action<T> action) where T : Control
        //{
        //    if (c.InvokeRequired)
        //    {
        //        c.Invoke(new Action(() => action(c)));
        //    }
        //    else
        //    {
        //        action(c);
        //    }
        //}
        public void UpdateImage(Bitmap image)
        {
            //string newText = "abc";
            this.OpenCVPictureBox.Invoke((MethodInvoker)delegate {
                // Running on the UI thread
                OpenCVPictureBox.Image = image;
                m_image = image;
                this.Refresh();
            });
            //m_image = m_OpenCvWrapper.GetBitMap("CV Image");
            //OpenCVPictureBox.Image = image;
            //m_image = image;
            //this.Refresh();
        }
        private void OpenCVPictureBox_Click(object sender, EventArgs e)
        {

        }

        private void EventHandlerForUpdateCvImageButton_Click(object sender, EventArgs e)
        {
            //m_OpenCvWrapper.TriggerUpdate();
            // Start the asynchronous operation.
            //backgroundWorker1.RunWorkerAsync();
        }
    }
}
