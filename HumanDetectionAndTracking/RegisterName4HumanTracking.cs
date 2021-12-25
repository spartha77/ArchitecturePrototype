using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using ManagedCommandsWrapper;
using System.Threading;


public delegate void UpdateImageDelegate(Bitmap bitmapImage);
public delegate void RestorePostUpdateImageDelegate();
namespace HumanDetectionAndTracking
{

    public partial class RegisterName4HumanTrackingForm : Form
    {

        int m_Counter = 0;
        private string m_ModelDirPath;
        private string m_DataDirPath;
        private string m_ImageDirPath;
        private string m_RegisteredName;
        private string m_PersonImageDirPath;
        private bool m_FormClose = false;
        ManagedCommandsWrapper.FaceRegistrationMode m_RegistrationMode;

        private OpenFileDialog m_OpenFileDialog;
        //private HumanDetectionAndTracking.AdaptiveHumanTrackingForm m_AdaptiveHumanTrackingForm;
        private MngdRegisterPersonCommand m_registerPersonCommand;

        private System.ComponentModel.BackgroundWorker m_backgroundWorkerForRegisterFaceCommandExecutor;


        // Update related delegates
        private UpdateImageDelegate m_UpdateImageDelegate;
        private RestorePostUpdateImageDelegate m_RestorePostUpdateImageDelegate;


        public void SetRestorePostUpdateImageDelegate(RestorePostUpdateImageDelegate restoreMethod)
        {
            m_RestorePostUpdateImageDelegate = new RestorePostUpdateImageDelegate(restoreMethod);
        }

        public RegisterName4HumanTrackingForm(UpdateImageDelegate updateMethod = null)
        {
            InitializeComponent();
            InitializeBackgroundWorker();
            InitializeFormCloseEventHandler();

            m_OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            //m_AdaptiveHumanTrackingForm = new HumanDetectionAndTracking.AdaptiveHumanTrackingForm();

            m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.OFFLINE;
            if (personNameRadioButton.Checked == true || batchModeRadioButton.Checked == true)
            {
                m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.OFFLINE;
            }
            else if (OnlineRegistrationRadioButton.Checked == true )
            {
                m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.ONLINE;
            }
            //m_registerPersonCommand = new MngdRegisterPersonCommand();
            //m_registerPersonCommand.SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateImage);

            if (updateMethod != null)
                m_UpdateImageDelegate = new UpdateImageDelegate(updateMethod);
            else
                m_UpdateImageDelegate = null;
        }

        private void InitializeBackgroundWorker()
        {
            m_backgroundWorkerForRegisterFaceCommandExecutor = new BackgroundWorker();
            m_backgroundWorkerForRegisterFaceCommandExecutor.DoWork +=
                new DoWorkEventHandler(BackgroundWorkerForRegisterFaceCommandExecutor_DoWork);

            m_backgroundWorkerForRegisterFaceCommandExecutor.RunWorkerCompleted +=
                new RunWorkerCompletedEventHandler(
            BackgroundWorkerForRegisterFaceCommandExecutor_RunWorker_Completed);
        }
        private void InitializeFormCloseEventHandler()
        {
            this.FormClosing += new FormClosingEventHandler(RegisterName4HumanTrackingForm_FormClosing);
        }
        private void RegisterName4HumanTrackingForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (m_Counter > 0)
            {
                if (MessageBox.Show("Form can not be closed when face registration is in progress. Please wait until the registration process is complete. ", "Form can not be closed",
                   MessageBoxButtons.OK, MessageBoxIcon.Stop) == DialogResult.OK)
                {
                    // Cancel the Closing event
                    e.Cancel = true;
                }
            }
            else
            {
                m_FormClose = true;
                this.Close();
            }
        }
        public bool IsRegistrationInProgress()
        {
            if (m_Counter > 0)
                return true;
            return false;
        }
        private void BackgroundWorkerForRegisterFaceCommandExecutor_RunWorker_Completed(
            object sender, RunWorkerCompletedEventArgs e)
        {
            //Thread.Sleep(100000);
            //this.Invoke((MethodInvoker)delegate {
            //    // Running on the UI thread

            //    //this./*m_AdaptiveHumanTrackingForm*/.Close();
            //});
            Interlocked.Decrement(ref m_Counter);

            if (!m_FormClose)
            {
                this.Invoke((MethodInvoker)delegate
                {
                    // Running on the UI thread

                    this.ExecuteCommandButton.Enabled = true;
                });
            }
            m_RestorePostUpdateImageDelegate();
        }
        // This event handler is where the actual,
        // potentially time-consuming work is done.
        private void BackgroundWorkerForRegisterFaceCommandExecutor_DoWork(object sender,
            DoWorkEventArgs e)
        {
            Interlocked.Increment(ref m_Counter);
            // Get the BackgroundWorker that raised this event.
            BackgroundWorker worker = sender as BackgroundWorker;
            Thread.CurrentThread.Priority = ThreadPriority.Highest;

            // Assign the result of the computation
            // to the Result property of the DoWorkEventArgs
            // object. This is will be available to the 
            // RunWorkerCompleted eventhandler.
            e.Result = CommandExecute();
            //Thread.Sleep(10000);
            //e.Result = 0;
        }
        private void UpdateImage(Bitmap image)
        {
            //m_AdaptiveHumanTrackingForm.UpdateImage(image);
            m_UpdateImageDelegate(image);
        }
        private void ModelDirectoryPathButton_Click(object sender, EventArgs e)
        {

            using (var fldrDlg = new FolderBrowserDialog())
            {
                if (fldrDlg.ShowDialog() == DialogResult.OK)
                {
                    m_ModelDirPath = fldrDlg.SelectedPath;
                    this.ModelDirectoryPathTextBox.Text = m_ModelDirPath;
                }
            }
        }

        private void DataDirectoryPathButton_Click(object sender, EventArgs e)
        {
            using (var fldrDlg = new FolderBrowserDialog())
            {
                if (fldrDlg.ShowDialog() == DialogResult.OK)
                {
                    m_DataDirPath = fldrDlg.SelectedPath;
                    this.DataDirectoryPathTextBox.Text = m_DataDirPath;
                }
            }            
        }

        private void ImageDirectoryPathButton_Click(object sender, EventArgs e)
        {
            using (var fldrDlg = new FolderBrowserDialog())
            {
                if (fldrDlg.ShowDialog() == DialogResult.OK)
                {
                    m_ImageDirPath = fldrDlg.SelectedPath;
                    this.ImageDirectoryPathTextBox.Text = m_ImageDirPath;
                }
            }            
        }

        bool IsInputValid()
        {
            if (!Directory.Exists(m_ModelDirPath))
            {
                string message = "";
                if (m_ModelDirPath.Length > 0)
                    message = "Please select Model Directory Path";
                else
                    message = m_ModelDirPath + "\t" + "Does not exist!!";
                string title = "Model Directory Path not valid";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, title, buttons, MessageBoxIcon.Error);
                if (result == DialogResult.OK)
                {
                    this.Close();
                    return false;
                }
            }

            if (!Directory.Exists(m_DataDirPath))
            {
                string message = "";
                if (m_DataDirPath.Length > 0)
                    message = "Please select Data Directory Path";
                else
                    message = m_DataDirPath + "\t" + "Does not exist!!";
                string title = "Data Directory Path not valid";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, title, buttons, MessageBoxIcon.Error);
                if (result == DialogResult.OK)
                {
                    this.Close();
                    return false;
                }
            }

            if (!Directory.Exists(m_ImageDirPath))
            {
                string message = "";
                if (m_ImageDirPath.Length > 0)
                    message = "Please select Image Directory Path";
                else
                    message = m_ImageDirPath + "\t" + "Does not exist!!";
                string title = "Image Directory Path not valid";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, title, buttons, MessageBoxIcon.Error);
                if (result == DialogResult.OK)
                {
                    this.Close();
                    return false;
                }
            }

            return true;
        }
        private void ExecuteCommandButton_Click(object sender, EventArgs e)
        {
            //this.Hide();
            //m_AdaptiveHumanTrackingForm.Show();
            ExecuteCommandButton.Enabled = false;
            if (m_backgroundWorkerForRegisterFaceCommandExecutor.IsBusy != true)
            {
                // Start the asynchronous operation.
                m_backgroundWorkerForRegisterFaceCommandExecutor.RunWorkerAsync();
            }
        }
        private int CommandExecute()
        {
            bool success = false;
            m_registerPersonCommand = new MngdRegisterPersonCommand();
            m_registerPersonCommand.SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateImage);
            //if (!IsInputValid())
            //    return 100;
            //m_ModelDirPath = @"C:\Users\partha3x\Desktop\Input\Models";
            //m_DataDirPath = @"C:\Users\partha3x\Desktop\Input\Models";
            //m_ImageDirPath = @"C:\Users\partha3x\Desktop\Input\Images";
            //m_RegisteredName = @"Vishnu";
            //m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.BY_PERSON_NAME_ONLINE;

            m_registerPersonCommand.ModelDirectoryPath = m_ModelDirPath;
            m_registerPersonCommand.DataDirectoryPath = m_DataDirPath;
            m_registerPersonCommand.RegistrationMode = m_RegistrationMode;


            if (batchModeRadioButton.Checked == true )
            {
                Console.WriteLine("Batch mode enabled\n");
                string[] m_ImageDirs = Directory.GetDirectories(m_ImageDirPath);
                Console.WriteLine("The number of directories starting with p is {0}.", m_ImageDirs.Length);
                foreach (string m_PersonImages in m_ImageDirs)
                {
                    Console.WriteLine(m_PersonImages);
                    string m_PersonName = new DirectoryInfo(m_PersonImages).Name;
                    Console.WriteLine(m_PersonName);
                    m_registerPersonCommand.ImageDirectoryPath = m_PersonImages;
                    m_registerPersonCommand.RegisteredName = m_PersonName;
                    m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.OFFLINE;
                    success = m_registerPersonCommand.Execute();
                }
            }
            else if (personNameRadioButton.Checked == true)
            {
                Console.WriteLine("person mode enabled\n");
                m_PersonImageDirPath = m_ImageDirPath + "\\" + m_RegisteredName;
                Console.WriteLine(m_PersonImageDirPath);
                if (Directory.Exists(m_PersonImageDirPath))
                {
                    m_registerPersonCommand.ImageDirectoryPath = m_PersonImageDirPath;
                    m_registerPersonCommand.RegisteredName = m_RegisteredName;
                    m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.OFFLINE;
                    success = m_registerPersonCommand.Execute();
                }
                else
                {
                    string message = "";
                    message = m_PersonImageDirPath + " " + "does not exist!! Please provide proper person name";
                    string title = "Mismatch in person name and Image folder";
                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    DialogResult result = MessageBox.Show(message, title, buttons, MessageBoxIcon.Error);
                }
            }
            else //if (m_RegistrationMode == ManagedCommandsWrapper.FaceRegistrationMode.BY_PERSON_NAME_ONLINE)
            {
                Console.WriteLine("person mode enabled\n");
                m_PersonImageDirPath = m_ImageDirPath + "\\" + m_RegisteredName;
                Console.WriteLine(m_PersonImageDirPath);
                if (!Directory.Exists(m_PersonImageDirPath))
                    System.IO.Directory.CreateDirectory(m_PersonImageDirPath);
                if (Directory.Exists(m_PersonImageDirPath))
                {
                    m_registerPersonCommand.ImageDirectoryPath = m_PersonImageDirPath;
                    m_registerPersonCommand.RegisteredName = m_RegisteredName;
                    m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.ONLINE;
                    success = m_registerPersonCommand.Execute();
                }
                //else
                //{
                //    string message = "";
                //    message = m_PersonImageDirPath + " " + "does not exist!! Please provide proper person name";
                //    string title = "Mismatch in person name and Image folder";
                //    MessageBoxButtons buttons = MessageBoxButtons.OK;
                //    DialogResult result = MessageBox.Show(message, title, buttons, MessageBoxIcon.Error);
                //}
            }

            //bool success = m_registerPersonCommand.Execute();

            //return error
            if (success)
                return 0;
            else
                return 100;
        }       

        private void AbortButton_Click(object sender, EventArgs e)
        {
            if (m_Counter > 0)
            {
                if (MessageBox.Show("Form can not be closed when face registration is in progress. Please wait until the registration process is complete. ", "Form can not be closed",
                   MessageBoxButtons.OK, MessageBoxIcon.Stop) == DialogResult.OK)
                {
                    // Cancel the Closing event
                    ;
                }
            }
            //else
            //    this.Close();
        }

        private void RegisterName4HumanTracking_Load(object sender, EventArgs e)
        {
            Console.WriteLine("RegisterName4HumanTracking_Load\n");
            
            this.batchModeRadioButton.Checked = true;
            //RadioButton radioButtonBatch = new RadioButton();
            //radioButtonBatch.Checked = true;
            /*
            Console.WriteLine("GroupBox\n");
            RadioButton radioButtonBatch = new RadioButton();
            RadioButton radioButtonName = new RadioButton();
            radioButtonBatch.Checked = true;
            radioButtonName.Checked = false;
            */
        }

        private void RegisteredNameTextBox_TextChanged(object sender, EventArgs e)
        {
            m_RegisteredName = RegisteredNameTextBox.Text;
        }

        private void ModelDirectoryPathTextBox_TextChanged(object sender, EventArgs e)
        {
            m_ModelDirPath = ModelDirectoryPathTextBox.Text;
        }

        private void DataDirectoryPathTextBox_TextChanged(object sender, EventArgs e)
        {
            m_DataDirPath = DataDirectoryPathTextBox.Text;
        }

        private void groupBoxMode_Enter(object sender, EventArgs e)
        {
            
        }

        private void batchModeRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            //Console.WriteLine("radioButtonBatch_CheckedChanged\n");
            //RadioButton radioButtonBatch = new RadioButton();
            //RadioButton radioButtonName = new RadioButton();
            //radioButtonBatch.Checked = true;
            //radioButtonName.Checked = false;
            //if (radioButtonBatch.Checked == true)
            //{
            //    Console.WriteLine("radioButtonBatch set\n");
            //}

            m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.OFFLINE;
        }

        private void personNameRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            //Console.WriteLine("radioButtonName_CheckedChanged\n");

            m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.OFFLINE;
            //RadioButton radioButtonBatch = new RadioButton();
            //RadioButton radioButtonName = new RadioButton();
            //radioButtonBatch.Checked = false;
            //radioButtonName.Checked = true;
        }

        private void ImageDirectoryPathTextBox_TextChanged(object sender, EventArgs e)
        {
            m_ImageDirPath = ImageDirectoryPathTextBox.Text;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void OnlineRegistrationRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            m_RegistrationMode = ManagedCommandsWrapper.FaceRegistrationMode.ONLINE;
        }
    }
}
