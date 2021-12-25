namespace HumanDetectionAndTracking
{
    partial class FaceDetectionForm
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
            this.ModelDirectoryPathButton = new System.Windows.Forms.Button();
            this.DataDirectoryPathButton = new System.Windows.Forms.Button();
            this.ModelDirectoryPathTextBox = new System.Windows.Forms.TextBox();
            this.DataDirectoryPathTextBox = new System.Windows.Forms.TextBox();
            this.ExecuteCommandButton = new System.Windows.Forms.Button();
            this.AbortButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ModelDirectoryPathButton
            // 
            this.ModelDirectoryPathButton.Location = new System.Drawing.Point(43, 67);
            this.ModelDirectoryPathButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.ModelDirectoryPathButton.Name = "ModelDirectoryPathButton";
            this.ModelDirectoryPathButton.Size = new System.Drawing.Size(142, 35);
            this.ModelDirectoryPathButton.TabIndex = 0;
            this.ModelDirectoryPathButton.Text = "Model Directory Path";
            this.ModelDirectoryPathButton.UseVisualStyleBackColor = true;
            this.ModelDirectoryPathButton.Click += new System.EventHandler(this.ModelDirectoryPathButton_Click);
            // 
            // DataDirectoryPathButton
            // 
            this.DataDirectoryPathButton.Location = new System.Drawing.Point(43, 132);
            this.DataDirectoryPathButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.DataDirectoryPathButton.Name = "DataDirectoryPathButton";
            this.DataDirectoryPathButton.Size = new System.Drawing.Size(142, 37);
            this.DataDirectoryPathButton.TabIndex = 1;
            this.DataDirectoryPathButton.Text = "Data Directory Path";
            this.DataDirectoryPathButton.UseVisualStyleBackColor = true;
            this.DataDirectoryPathButton.Click += new System.EventHandler(this.DataDirectoryPathButton_Click);
            // 
            // ModelDirectoryPathTextBox
            // 
            this.ModelDirectoryPathTextBox.Location = new System.Drawing.Point(218, 76);
            this.ModelDirectoryPathTextBox.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.ModelDirectoryPathTextBox.Name = "ModelDirectoryPathTextBox";
            this.ModelDirectoryPathTextBox.Size = new System.Drawing.Size(360, 20);
            this.ModelDirectoryPathTextBox.TabIndex = 2;
            // 
            // DataDirectoryPathTextBox
            // 
            this.DataDirectoryPathTextBox.Location = new System.Drawing.Point(218, 141);
            this.DataDirectoryPathTextBox.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.DataDirectoryPathTextBox.Name = "DataDirectoryPathTextBox";
            this.DataDirectoryPathTextBox.Size = new System.Drawing.Size(360, 20);
            this.DataDirectoryPathTextBox.TabIndex = 3;
            // 
            // ExecuteCommandButton
            // 
            this.ExecuteCommandButton.Location = new System.Drawing.Point(218, 234);
            this.ExecuteCommandButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.ExecuteCommandButton.Name = "ExecuteCommandButton";
            this.ExecuteCommandButton.Size = new System.Drawing.Size(137, 36);
            this.ExecuteCommandButton.TabIndex = 4;
            this.ExecuteCommandButton.Text = "Execute Command";
            this.ExecuteCommandButton.UseVisualStyleBackColor = true;
            this.ExecuteCommandButton.Click += new System.EventHandler(this.ExecuteCommandButton_Click);
            // 
            // AbortButton
            // 
            this.AbortButton.Location = new System.Drawing.Point(390, 234);
            this.AbortButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.AbortButton.Name = "AbortButton";
            this.AbortButton.Size = new System.Drawing.Size(127, 36);
            this.AbortButton.TabIndex = 5;
            this.AbortButton.Text = "Abort";
            this.AbortButton.UseVisualStyleBackColor = true;
            this.AbortButton.Click += new System.EventHandler(this.AbortButton_Click);
            // 
            // FaceDetectionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(608, 308);
            this.Controls.Add(this.AbortButton);
            this.Controls.Add(this.ExecuteCommandButton);
            this.Controls.Add(this.DataDirectoryPathTextBox);
            this.Controls.Add(this.ModelDirectoryPathTextBox);
            this.Controls.Add(this.DataDirectoryPathButton);
            this.Controls.Add(this.ModelDirectoryPathButton);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "FaceDetectionForm";
            this.Text = "Skill : Face Detection";
            this.Load += new System.EventHandler(this.FaceDetection_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ModelDirectoryPathButton;
        private System.Windows.Forms.Button DataDirectoryPathButton;
        private System.Windows.Forms.TextBox ModelDirectoryPathTextBox;
        private System.Windows.Forms.TextBox DataDirectoryPathTextBox;
        private System.Windows.Forms.Button ExecuteCommandButton;
        private System.Windows.Forms.Button AbortButton;
    }
}