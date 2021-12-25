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
using System.Threading;
using ManagedCommandsWrapper;


namespace HumanDetectionAndTracking
{
    public partial class SkillExecuteInputForm : Form
    {
        private string m_ModelDirPath;
        private string m_DataDirPath;

        private OpenFileDialog m_OpenFileDialog;
        private bool m_FormClose = false;

        //private HumanDetectionAndTracking.AdaptiveHumanTrackingForm m_AdaptiveHumanTrackingForm;
        private IAbstractSkill m_AbstractSkill;
        

        private System.ComponentModel.BackgroundWorker m_backgroundWorkerForSkillExecutor;

        // Update related delegates
        private UpdateImageDelegate m_UpdateImageDelegate;
        private RestorePostUpdateImageDelegate m_RestorePostUpdateImageDelegate;

        public void SetRestorePostUpdateImageDelegate(RestorePostUpdateImageDelegate restoreMethod)
        {
            m_RestorePostUpdateImageDelegate = new RestorePostUpdateImageDelegate(restoreMethod);
        }
        public SkillExecuteInputForm(HumanDetectionAndTracking.SkillType skillType, UpdateImageDelegate updateMethod = null)
        {
            InitializeComponent();
            InitializeBackgroundWorker();
            InitializeFormCloseEventHandler();

            m_OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            //m_AdaptiveHumanTrackingForm = new HumanDetectionAndTracking.AdaptiveHumanTrackingForm();

            switch (skillType)
            {
                case HumanDetectionAndTracking.SkillType.Face_Identification:
                    m_AbstractSkill = new MngdFaceIdentificationCommand();
                    this.Text = @"Skill : Face Identification";
                    break;
                case HumanDetectionAndTracking.SkillType.Face_Detection:
                    m_AbstractSkill = new MngdFaceDetectionCommand();
                    this.Text = @"Skill : Face Detection";
                    break;
                case HumanDetectionAndTracking.SkillType.Body_Identification:
                    m_AbstractSkill = new MngdBodyIdCommand();
                    this.Text = @"Skill : Body Identification";
                    break;
                case HumanDetectionAndTracking.SkillType.Human_Detection:
                    m_AbstractSkill = new MngdHumanDetectionCommand();
                    this.Text = @"Skill : Human Tracking";
                    break;
                case HumanDetectionAndTracking.SkillType.Identify_Person:
                    m_AbstractSkill = new MngdIdentifyPersonCommand();
                    this.Text = @"Skill : Person Identification";
                    break;
            }

            m_AbstractSkill.SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateImage);

            if (updateMethod != null)
                m_UpdateImageDelegate = new UpdateImageDelegate(updateMethod);
            else
                m_UpdateImageDelegate = null;
        }
        private void InitializeBackgroundWorker()
        {
            m_backgroundWorkerForSkillExecutor = new BackgroundWorker();
            m_backgroundWorkerForSkillExecutor.DoWork +=
                new DoWorkEventHandler(m_backgroundWorkerForSkillExecutor_DoWork);

            m_backgroundWorkerForSkillExecutor.RunWorkerCompleted +=
                new RunWorkerCompletedEventHandler(
            m_backgroundWorkerForSkillExecutor_RunWorker_Completed);
        }
        private void InitializeFormCloseEventHandler()
        {
            this.FormClosing += new FormClosingEventHandler(SkillExecutorForm_FormClosing);
        }
        private void SkillExecutorForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //TODO 
            // Abort the command from here
            m_FormClose = true;
            AbortCommand();
        }
        public void AbortCommand()
        {
            m_AbstractSkill.Terminate();
        }
        private void m_backgroundWorkerForSkillExecutor_DoWork(object sender,
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
        private void m_backgroundWorkerForSkillExecutor_RunWorker_Completed(
            object sender, RunWorkerCompletedEventArgs e)
        {
            //Thread.Sleep(100000);
            //this.Invoke((MethodInvoker)delegate {
            //    // Running on the UI thread

            //    //this./*m_AdaptiveHumanTrackingForm*/.Close();
            //});
            //Interlocked.Decrement(ref m_Counter);
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
        private void UpdateImage(Bitmap image)
        {
            m_UpdateImageDelegate(image);
        }
        private void ModelDirectoryPathButton_Click(object sender, EventArgs e)
        {
            using (var fldrDlg = new FolderBrowserDialog())
            {
                //fldrDlg.Filter = "Png Files (*.png)|*.png";
                //fldrDlg.Filter = "Excel Files (*.xls, *.xlsx)|*.xls;*.xlsx|CSV Files (*.csv)|*.csv"

                if (fldrDlg.ShowDialog() == DialogResult.OK)
                {
                    //fldrDlg.SelectedPath -- your result
                    m_ModelDirPath = fldrDlg.SelectedPath;
                    this.ModelDirectoryPathTextBox.Text = m_ModelDirPath;
                }
            }
        }

        private void DataDirectoryPathButton_Click(object sender, EventArgs e)
        {
            using (var fldrDlg = new FolderBrowserDialog())
            {
                //fldrDlg.Filter = "Png Files (*.png)|*.png";
                //fldrDlg.Filter = "Excel Files (*.xls, *.xlsx)|*.xls;*.xlsx|CSV Files (*.csv)|*.csv"

                if (fldrDlg.ShowDialog() == DialogResult.OK)
                {
                    //fldrDlg.SelectedPath -- your result
                    m_DataDirPath = fldrDlg.SelectedPath;
                    this.DataDirectoryPathTextBox.Text = m_DataDirPath;
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

            return true;
        }
        private int CommandExecute()
        {
            bool success = false;
            if (!IsInputValid())
                return 10;

            //MngdFaceIdentificationCommand m_AbstractSkill = new MngdFaceIdentificationCommand();
            m_AbstractSkill.ModelDirectoryPath = m_ModelDirPath;
            m_AbstractSkill.DataDirectoryPath = m_DataDirPath;
            success = m_AbstractSkill.Execute();

            if (success)
                return 0;
            else
                return 100;
        }
        private void ExecuteCommandButton_Click(object sender, EventArgs e)
        {
            ExecuteCommandButton.Enabled = false;
            if (m_backgroundWorkerForSkillExecutor.IsBusy != true)
            {
                // Start the asynchronous operation.
                m_backgroundWorkerForSkillExecutor.RunWorkerAsync();
            }
        }

        private void FaceIdentification_Load(object sender, EventArgs e)
        {

        }

        private void AbortButton_Click(object sender, EventArgs e)
        {
            AbortCommand();
            //this.Close();
        }

        private void ModelDirectoryPathTextBox_TextChanged(object sender, EventArgs e)
        {
            m_ModelDirPath = ModelDirectoryPathTextBox.Text;
        }

        private void DataDirectoryPathTextBox_TextChanged(object sender, EventArgs e)
        {
            m_DataDirPath = DataDirectoryPathTextBox.Text;
        }

        private void SkillIExecutenputForm_Load(object sender, EventArgs e)
        {

        }
    }
}
