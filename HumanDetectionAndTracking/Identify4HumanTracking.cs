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
using System.Runtime.InteropServices;

namespace HumanDetectionAndTracking
{
    public partial class Identify4HumanTracking : Form
    {
        private string m_ModelDirPath;
        private string m_DataDirPath;

        private OpenFileDialog m_OpenFileDialog;
        private HumanDetectionAndTracking.AdaptiveHumanTrackingForm m_AdaptiveHumanTrackingForm;
        private MngdIdentifyPersonCommand m_IdentifyPersonCommand;
               
        public Identify4HumanTracking()
        {
            InitializeComponent();
            m_OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            m_AdaptiveHumanTrackingForm = new HumanDetectionAndTracking.AdaptiveHumanTrackingForm();

            m_IdentifyPersonCommand = new MngdIdentifyPersonCommand();
            m_IdentifyPersonCommand.SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateImage);
        }
        private void UpdateImage(Bitmap image)
        {
            m_AdaptiveHumanTrackingForm.UpdateImage(image);
        }

        private void Identify4HumanTracking_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

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
            //OpenFileDialog folderBrowser = new OpenFileDialog();
            //// Set validate names and check file exists to false otherwise windows will
            //// not let you select "Folder Selection."
            //folderBrowser.ValidateNames = false;
            //folderBrowser.CheckFileExists = false;
            //folderBrowser.CheckPathExists = true;
            //// Always default to Folder Selection.
            //folderBrowser.FileName = "Folder Selection.";
            //if (folderBrowser.ShowDialog() == DialogResult.OK)
            //{
            //    string folderPath = Path.GetDirectoryName(folderBrowser.FileName);
            //    m_DataDirPath = folderPath;
            //}
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
            //using (var fbd = new FolderBrowserDialog())
            //{
            //    DialogResult result = fbd.ShowDialog();

            //    if (result == DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
            //    {
            //        string[] files = Directory.GetFiles(fbd.SelectedPath);

            //        System.Windows.Forms.MessageBox.Show("Files found: " + files.Length.ToString(), "Message");
            //    }
            //}
            //if (m_OpenFileDialog.ShowDialog() == DialogResult.OK)
            //{
            //    try
            //    {
            //        m_ModelDirPath = m_OpenFileDialog.FileName;
            //        this.ModelDirectoryPathTextBox.Text = m_ModelDirPath;

            //    }
            //    catch (Exception ex)
            //    {
            //        MessageBox.Show("Security error.\n\nError message: {ex.Message}\n\n" +
            //        "Details:\n\n{ex.StackTrace}");
            //    }
            //}
            //   OpenFileDialog folderBrowser = new OpenFileDialog();
            //// Set validate names and check file exists to false otherwise windows will
            //// not let you select "Folder Selection."
            //folderBrowser.ValidateNames = false;
            //folderBrowser.CheckFileExists = false;
            //folderBrowser.CheckPathExists = true;
            //// Always default to Folder Selection.
            //folderBrowser.FileName = "Folder Selection.";
            //if (folderBrowser.ShowDialog() == DialogResult.OK)
            //{
            //    string folderPath = Path.GetDirectoryName(folderBrowser.FileName);
            //    m_ModelDirPath = folderPath;
            //}
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
        private void AbortButton_Click(object sender, EventArgs e)
        {
            
            this.Close();
        }

        private void ExecuteCommandButton_Click(object sender, EventArgs e)
        {
            if (!IsInputValid())
                return;
            m_AdaptiveHumanTrackingForm.Show();
            //MngdIdentifyPersonCommand m_IdentifyPersonCommand = new MngdIdentifyPersonCommand();
            m_IdentifyPersonCommand.ModelDirectoryPath = m_ModelDirPath;
            m_IdentifyPersonCommand.DataDirectoryPath = m_DataDirPath;
            m_IdentifyPersonCommand.Execute();
        }
    }
}
