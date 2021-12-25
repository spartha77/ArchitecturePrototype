using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace HumanDetectionAndTracking
{
    public enum  SkillType
    {
        Face_Registration,
        Face_Detection,
        Face_Identification,
        Body_Identification,
        Human_Detection,
        Identify_Person
    };
    public partial class HumanDetectionAndTrackingParentForm : Form
    {

        Image m_DefaultImage;
        HumanDetectionAndTracking.RegisterName4HumanTrackingForm m_RegistrationForm;
        HumanDetectionAndTracking.SkillExecuteInputForm m_SkillExecuteInputForm;

        public HumanDetectionAndTrackingParentForm()
        {
            InitializeComponent();
            m_DefaultImage = this.outputImagePictureBox.Image;
            this.FormClosing += new FormClosingEventHandler(HumanDetectionAndTrackingParentForm_FormClosing);
        }
        private void HumanDetectionAndTrackingParentForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (m_RegistrationForm != null )
            {
                if ( m_RegistrationForm.IsRegistrationInProgress())
                {
                    if (MessageBox.Show("Face registration in progress. Abnormal termination might result in incomplete registration of face(s). Do you still want to cancel? ", "Face registration in progress",
                   MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                    {
                        // Cancel the Closing event
                        e.Cancel = true;

                    }
                    
                }
            }
            else if (m_SkillExecuteInputForm != null )
            {
                m_SkillExecuteInputForm.AbortCommand();
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            //AllocConsole();
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();
        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
        public void UpdateImage(Bitmap image)
        {   
            this.outputImagePictureBox.Invoke((MethodInvoker)delegate {
                // Running on the UI thread
                outputImagePictureBox.Image = image;
                this.Refresh();
            });
        }
        public void RestorePostUpdateImage()
        {
            this.outputImagePictureBox.Invoke((MethodInvoker)delegate {
                // Running on the UI thread
                outputImagePictureBox.Image = m_DefaultImage;
                this.Refresh();
            });
            
        }
        private void registerNameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_RegistrationForm =
                new HumanDetectionAndTracking.RegisterName4HumanTrackingForm(UpdateImage);
            m_RegistrationForm.SetRestorePostUpdateImageDelegate(RestorePostUpdateImage);
            m_RegistrationForm.ShowDialog(this);
        }

        private void adaptivePersonIdentificationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_SkillExecuteInputForm =
                new HumanDetectionAndTracking.SkillExecuteInputForm(HumanDetectionAndTracking.SkillType.Identify_Person,
                UpdateImage);
            m_SkillExecuteInputForm.SetRestorePostUpdateImageDelegate(RestorePostUpdateImage);
            m_SkillExecuteInputForm.ShowDialog(this);
        }

        private void humanDetectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_SkillExecuteInputForm =
                new HumanDetectionAndTracking.SkillExecuteInputForm(HumanDetectionAndTracking.SkillType.Human_Detection,
                UpdateImage);
            m_SkillExecuteInputForm.SetRestorePostUpdateImageDelegate(RestorePostUpdateImage);
            m_SkillExecuteInputForm.ShowDialog(this);
        }

        private void bodyIdentificationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_SkillExecuteInputForm =
                new HumanDetectionAndTracking.SkillExecuteInputForm(HumanDetectionAndTracking.SkillType.Body_Identification,
                UpdateImage);
            m_SkillExecuteInputForm.SetRestorePostUpdateImageDelegate(RestorePostUpdateImage);
            m_SkillExecuteInputForm.ShowDialog(this);
        }

        private void faceDetectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_SkillExecuteInputForm =
                new HumanDetectionAndTracking.SkillExecuteInputForm(HumanDetectionAndTracking.SkillType.Face_Detection,
                UpdateImage);
            m_SkillExecuteInputForm.SetRestorePostUpdateImageDelegate(RestorePostUpdateImage);
            m_SkillExecuteInputForm.ShowDialog(this);

        }

        private void faceIdentificationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_SkillExecuteInputForm = 
                new HumanDetectionAndTracking.SkillExecuteInputForm(HumanDetectionAndTracking.SkillType.Face_Identification, 
                UpdateImage);
            m_SkillExecuteInputForm.SetRestorePostUpdateImageDelegate(RestorePostUpdateImage);
            m_SkillExecuteInputForm.ShowDialog(this);
        }

        private void commandsToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
