namespace HumanDetectionAndTracking
{
    partial class HumanDetection
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
            this.ModelDirectoryPathButton.Location = new System.Drawing.Point(48, 63);
            this.ModelDirectoryPathButton.Name = "ModelDirectoryPathButton";
            this.ModelDirectoryPathButton.Size = new System.Drawing.Size(188, 40);
            this.ModelDirectoryPathButton.TabIndex = 0;
            this.ModelDirectoryPathButton.Text = "Model Directory Path";
            this.ModelDirectoryPathButton.UseVisualStyleBackColor = true;
            this.ModelDirectoryPathButton.Click += new System.EventHandler(this.ModelDirectoryPathButton_Click);
            // 
            // DataDirectoryPathButton
            // 
            this.DataDirectoryPathButton.Location = new System.Drawing.Point(52, 137);
            this.DataDirectoryPathButton.Name = "DataDirectoryPathButton";
            this.DataDirectoryPathButton.Size = new System.Drawing.Size(183, 37);
            this.DataDirectoryPathButton.TabIndex = 1;
            this.DataDirectoryPathButton.Text = "Data Directory Path";
            this.DataDirectoryPathButton.UseVisualStyleBackColor = true;
            this.DataDirectoryPathButton.Click += new System.EventHandler(this.DataDirectoryPathButton_Click);
            // 
            // ModelDirectoryPathTextBox
            // 
            this.ModelDirectoryPathTextBox.Location = new System.Drawing.Point(277, 72);
            this.ModelDirectoryPathTextBox.Name = "ModelDirectoryPathTextBox";
            this.ModelDirectoryPathTextBox.Size = new System.Drawing.Size(466, 22);
            this.ModelDirectoryPathTextBox.TabIndex = 2;
            // 
            // DataDirectoryPathTextBox
            // 
            this.DataDirectoryPathTextBox.Location = new System.Drawing.Point(277, 144);
            this.DataDirectoryPathTextBox.Name = "DataDirectoryPathTextBox";
            this.DataDirectoryPathTextBox.Size = new System.Drawing.Size(465, 22);
            this.DataDirectoryPathTextBox.TabIndex = 3;
            // 
            // ExecuteCommandButton
            // 
            this.ExecuteCommandButton.Location = new System.Drawing.Point(277, 249);
            this.ExecuteCommandButton.Name = "ExecuteCommandButton";
            this.ExecuteCommandButton.Size = new System.Drawing.Size(145, 39);
            this.ExecuteCommandButton.TabIndex = 4;
            this.ExecuteCommandButton.Text = "Execute Command";
            this.ExecuteCommandButton.UseVisualStyleBackColor = true;
            this.ExecuteCommandButton.Click += new System.EventHandler(this.ExecuteCommandButton_Click);
            // 
            // AbortButton
            // 
            this.AbortButton.Location = new System.Drawing.Point(476, 249);
            this.AbortButton.Name = "AbortButton";
            this.AbortButton.Size = new System.Drawing.Size(140, 39);
            this.AbortButton.TabIndex = 5;
            this.AbortButton.Text = "Abort";
            this.AbortButton.UseVisualStyleBackColor = true;
            this.AbortButton.Click += new System.EventHandler(this.AbortButton_Click);
            // 
            // HumanDetection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 362);
            this.Controls.Add(this.AbortButton);
            this.Controls.Add(this.ExecuteCommandButton);
            this.Controls.Add(this.DataDirectoryPathTextBox);
            this.Controls.Add(this.ModelDirectoryPathTextBox);
            this.Controls.Add(this.DataDirectoryPathButton);
            this.Controls.Add(this.ModelDirectoryPathButton);
            this.Name = "HumanDetection";
            this.Text = "HumanDetection";
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