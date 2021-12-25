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

namespace HumanDetectionAndTracking
{
    public partial class BodyId : Form
    {
        private string m_ModelDirPath;
        private string m_DataDirPath;

        private OpenFileDialog m_OpenFileDialog;
        private HumanDetectionAndTracking.AdaptiveHumanTrackingForm m_AdaptiveHumanTrackingForm;
        private MngdBodyIdCommand m_BodyIdCommand;
        public BodyId()
        {
            InitializeComponent();
            m_OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            m_AdaptiveHumanTrackingForm = new HumanDetectionAndTracking.AdaptiveHumanTrackingForm();

            m_BodyIdCommand = new MngdBodyIdCommand();
            m_BodyIdCommand.SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateImage);
        }
        private void UpdateImage(Bitmap image)
        {
            m_AdaptiveHumanTrackingForm.UpdateImage(image);
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

        private void ModelDirectoryPathtextBox_TextChanged(object sender, EventArgs e)
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
        private void DataDirectoryPathtextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void ExecuteCommandButton_Click(object sender, EventArgs e)
        {
            if (!IsInputValid())
                return;
            m_AdaptiveHumanTrackingForm.Show();
            //MngdBodyIdCommand m_BodyIdCommand = new MngdBodyIdCommand();
            m_BodyIdCommand.ModelDirectoryPath = m_ModelDirPath;
            m_BodyIdCommand.DataDirectoryPath = m_DataDirPath;
            m_BodyIdCommand.Execute();

        }

        private void AbortButton_Click(object sender, EventArgs e)
        {
            this.Close();

        }
    }
}
