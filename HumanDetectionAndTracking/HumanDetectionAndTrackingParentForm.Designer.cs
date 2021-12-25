namespace HumanDetectionAndTracking
{
    partial class HumanDetectionAndTrackingParentForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(HumanDetectionAndTrackingParentForm));
            this.outputImagePictureBox = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.commandsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.registerNameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.identificationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.adaptivePersonIdentificationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.faceDetectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.faceIdentificationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.humanDetectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bodyIdentificationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.outputImagePictureBox)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // outputImagePictureBox
            // 
            this.outputImagePictureBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.outputImagePictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.outputImagePictureBox.Image = ((System.Drawing.Image)(resources.GetObject("outputImagePictureBox.Image")));
            this.outputImagePictureBox.Location = new System.Drawing.Point(0, 24);
            this.outputImagePictureBox.Name = "outputImagePictureBox";
            this.outputImagePictureBox.Size = new System.Drawing.Size(984, 617);
            this.outputImagePictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.outputImagePictureBox.TabIndex = 0;
            this.outputImagePictureBox.TabStop = false;
            this.outputImagePictureBox.Click += new System.EventHandler(this.pictureBox1_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.commandsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(984, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // commandsToolStripMenuItem
            // 
            this.commandsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.registerNameToolStripMenuItem,
            this.identificationToolStripMenuItem});
            this.commandsToolStripMenuItem.Name = "commandsToolStripMenuItem";
            this.commandsToolStripMenuItem.Size = new System.Drawing.Size(45, 20);
            this.commandsToolStripMenuItem.Text = "Skills";
            this.commandsToolStripMenuItem.Click += new System.EventHandler(this.commandsToolStripMenuItem_Click);
            // 
            // registerNameToolStripMenuItem
            // 
            this.registerNameToolStripMenuItem.Name = "registerNameToolStripMenuItem";
            this.registerNameToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.registerNameToolStripMenuItem.Text = "Registration";
            this.registerNameToolStripMenuItem.Click += new System.EventHandler(this.registerNameToolStripMenuItem_Click);
            // 
            // identificationToolStripMenuItem
            // 
            this.identificationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.adaptivePersonIdentificationToolStripMenuItem,
            this.faceDetectionToolStripMenuItem,
            this.faceIdentificationToolStripMenuItem,
            this.humanDetectionToolStripMenuItem,
            this.bodyIdentificationToolStripMenuItem});
            this.identificationToolStripMenuItem.Name = "identificationToolStripMenuItem";
            this.identificationToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.identificationToolStripMenuItem.Text = "Identification";
            // 
            // adaptivePersonIdentificationToolStripMenuItem
            // 
            this.adaptivePersonIdentificationToolStripMenuItem.Name = "adaptivePersonIdentificationToolStripMenuItem";
            this.adaptivePersonIdentificationToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.adaptivePersonIdentificationToolStripMenuItem.Text = "Fusion";
            this.adaptivePersonIdentificationToolStripMenuItem.Click += new System.EventHandler(this.adaptivePersonIdentificationToolStripMenuItem_Click);
            // 
            // faceDetectionToolStripMenuItem
            // 
            this.faceDetectionToolStripMenuItem.Name = "faceDetectionToolStripMenuItem";
            this.faceDetectionToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.faceDetectionToolStripMenuItem.Text = "Face Detection";
            this.faceDetectionToolStripMenuItem.Click += new System.EventHandler(this.faceDetectionToolStripMenuItem_Click);
            // 
            // faceIdentificationToolStripMenuItem
            // 
            this.faceIdentificationToolStripMenuItem.Name = "faceIdentificationToolStripMenuItem";
            this.faceIdentificationToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.faceIdentificationToolStripMenuItem.Text = "Face Identification";
            this.faceIdentificationToolStripMenuItem.Click += new System.EventHandler(this.faceIdentificationToolStripMenuItem_Click);
            // 
            // humanDetectionToolStripMenuItem
            // 
            this.humanDetectionToolStripMenuItem.Name = "humanDetectionToolStripMenuItem";
            this.humanDetectionToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.humanDetectionToolStripMenuItem.Text = "Human Detection";
            this.humanDetectionToolStripMenuItem.Click += new System.EventHandler(this.humanDetectionToolStripMenuItem_Click);
            // 
            // bodyIdentificationToolStripMenuItem
            // 
            this.bodyIdentificationToolStripMenuItem.Name = "bodyIdentificationToolStripMenuItem";
            this.bodyIdentificationToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.bodyIdentificationToolStripMenuItem.Text = "Body Identification";
            this.bodyIdentificationToolStripMenuItem.Click += new System.EventHandler(this.bodyIdentificationToolStripMenuItem_Click);
            // 
            // HumanDetectionAndTrackingParentForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(984, 641);
            this.Controls.Add(this.outputImagePictureBox);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "HumanDetectionAndTrackingParentForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Human Detection and Tracking";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.outputImagePictureBox)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox outputImagePictureBox;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem commandsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem registerNameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem identificationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem adaptivePersonIdentificationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem faceDetectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem faceIdentificationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem humanDetectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem bodyIdentificationToolStripMenuItem;
    }
}

