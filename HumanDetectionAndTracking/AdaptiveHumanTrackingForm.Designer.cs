namespace HumanDetectionAndTracking
{
    partial class AdaptiveHumanTrackingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.OpenCVPictureBox = new System.Windows.Forms.PictureBox();
            this.EventHandlerForUpdateCvImageButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.OpenCVPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // OpenCVPictureBox
            // 
            this.OpenCVPictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.OpenCVPictureBox.Location = new System.Drawing.Point(0, 0);
            this.OpenCVPictureBox.Name = "OpenCVPictureBox";
            this.OpenCVPictureBox.Size = new System.Drawing.Size(797, 450);
            this.OpenCVPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.OpenCVPictureBox.TabIndex = 0;
            this.OpenCVPictureBox.TabStop = false;
            this.OpenCVPictureBox.Click += new System.EventHandler(this.OpenCVPictureBox_Click);
            // 
            // EventHandlerForUpdateCvImageButton
            // 
            this.EventHandlerForUpdateCvImageButton.Location = new System.Drawing.Point(30, 25);
            this.EventHandlerForUpdateCvImageButton.Name = "EventHandlerForUpdateCvImageButton";
            this.EventHandlerForUpdateCvImageButton.Size = new System.Drawing.Size(134, 36);
            this.EventHandlerForUpdateCvImageButton.TabIndex = 1;
            this.EventHandlerForUpdateCvImageButton.Text = "Update CV Image";
            this.EventHandlerForUpdateCvImageButton.UseVisualStyleBackColor = true;
            this.EventHandlerForUpdateCvImageButton.Click += new System.EventHandler(this.EventHandlerForUpdateCvImageButton_Click);
            // 
            // AdaptiveHumanTrackingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(797, 450);
            this.Controls.Add(this.EventHandlerForUpdateCvImageButton);
            this.Controls.Add(this.OpenCVPictureBox);
            this.Name = "AdaptiveHumanTrackingForm";
            this.Text = "Adaptive Human Tracking";
            this.Load += new System.EventHandler(this.AdaptiveHumanTrackingForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.OpenCVPictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox OpenCVPictureBox;
        private System.Windows.Forms.Button EventHandlerForUpdateCvImageButton;
    }
}