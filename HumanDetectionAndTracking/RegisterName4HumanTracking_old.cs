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

namespace HumanDetectionAndTracking
{
    public partial class RegisterName4HumanTracking : Form
    {
        private string m_ModelDirPath;
        private string m_DataDirPath;
        private string m_ImageDirPath;
        private string m_RegisteredName;

        private OpenFileDialog m_OpenFileDialog;
        private HumanDetectionAndTracking.AdaptiveHumanTrackingForm m_AdaptiveHumanTrackingForm;
        private MngdRegisterPersonCommand m_registerPersonCommand;

        private System.ComponentModel.BackgroundWorker m_backgroundWorkerForRegisterFaceCommandExecutor;

        public RegisterName4HumanTracking()
        {
            InitializeComponent();
            InitializeBackgroundWorker();

            m_OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            m_registerPersonCommand = new MngdRegisterPersonCommand();
            m_AdaptiveHumanTrackingForm = new HumanDetectionAndTracking.AdaptiveHumanTrackingForm();
            m_registerPersonCommand.SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateImage);
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
        private void BackgroundWorkerForRegisterFaceCommandExecutor_RunWorker_Completed(
            object sender, RunWorkerCompletedEventArgs e)
        {
            //Thread.Sleep(100000);
            this.Invoke((MethodInvoker)delegate {
                // Running on the UI thread
                
                //this.m_AdaptiveHumanTrackingForm.Close();
            });
        }
        // This event handler is where the actual,
        // potentially time-consuming work is done.
        private void BackgroundWorkerForRegisterFaceCommandExecutor_DoWork(object sender,
            DoWorkEventArgs e)
        {
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
            m_AdaptiveHumanTrackingForm.UpdateImage(image);
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
                    //fldrDlg.SelectedPath -- your result
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
                    //fldrDlg.SelectedPath -- your result
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
            m_AdaptiveHumanTrackingForm.Show();
            if (m_backgroundWorkerForRegisterFaceCommandExecutor.IsBusy != true)
            {
                // Start the asynchronous operation.
                m_backgroundWorkerForRegisterFaceCommandExecutor.RunWorkerAsync();
            }
        }
        private int CommandExecute()
        {
            //if (!IsInputValid())
            //    return 100;

            m_registerPersonCommand.ModelDirectoryPath = m_ModelDirPath;
            m_registerPersonCommand.DataDirectoryPath = m_DataDirPath;
            m_registerPersonCommand.ImageDirectoryPath = m_ImageDirPath;
            m_registerPersonCommand.RegisteredName = m_RegisteredName;

            //m_registerPersonCommand.ModelDirectoryPath = "C:\\Input\\Models";
            //m_registerPersonCommand.DataDirectoryPath = "C:\\Input\\Models";
            //m_registerPersonCommand.ImageDirectoryPath = "C:\\Input\\Images";
            //m_registerPersonCommand.RegisteredName = "Vishnu";

            bool success = m_registerPersonCommand.Execute();
            
            //return error
            if (success)
                return 0;
            else
                return 100;
        }
        private void AbortButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void RegisterName4HumanTracking_Load(object sender, EventArgs e)
        {
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            m_RegisteredName = textBox1.Text;
        }

        private void ModelDirectoryPathTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void DataDirectoryPathTextBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
