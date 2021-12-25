namespace HumanDetectionAndTracking
{
    partial class Identify4HumanTracking
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
            this.DataDirectoryPathButton = new System.Windows.Forms.Button();
            this.ModelDirectoryPathButton = new System.Windows.Forms.Button();
            this.ModelDirectoryPathTextBox = new System.Windows.Forms.TextBox();
            this.DataDirectoryPathTextBox = new System.Windows.Forms.TextBox();
            this.ExecuteCommandButton = new System.Windows.Forms.Button();
            this.AbortButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // DataDirectoryPathButton
            // 
            this.DataDirectoryPathButton.Location = new System.Drawing.Point(48, 118);
            this.DataDirectoryPathButton.Name = "DataDirectoryPathButton";
            this.DataDirectoryPathButton.Size = new System.Drawing.Size(168, 37);
            this.DataDirectoryPathButton.TabIndex = 1;
            this.DataDirectoryPathButton.Text = "Data Directory Path";
            this.DataDirectoryPathButton.UseVisualStyleBackColor = true;
            this.DataDirectoryPathButton.Click += new System.EventHandler(this.DataDirectoryPathButton_Click);
            // 
            // ModelDirectoryPathButton
            // 
            this.ModelDirectoryPathButton.Location = new System.Drawing.Point(48, 53);
            this.ModelDirectoryPathButton.Name = "ModelDirectoryPathButton";
            this.ModelDirectoryPathButton.Size = new System.Drawing.Size(168, 41);
            this.ModelDirectoryPathButton.TabIndex = 2;
            this.ModelDirectoryPathButton.Text = "Model Directory Path";
            this.ModelDirectoryPathButton.UseVisualStyleBackColor = true;
            this.ModelDirectoryPathButton.Click += new System.EventHandler(this.ModelDirectoryPathButton_Click);
            // 
            // ModelDirectoryPathTextBox
            // 
            this.ModelDirectoryPathTextBox.Location = new System.Drawing.Point(257, 62);
            this.ModelDirectoryPathTextBox.Name = "ModelDirectoryPathTextBox";
            this.ModelDirectoryPathTextBox.Size = new System.Drawing.Size(483, 22);
            this.ModelDirectoryPathTextBox.TabIndex = 4;
            // 
            // DataDirectoryPathTextBox
            // 
            this.DataDirectoryPathTextBox.Location = new System.Drawing.Point(257, 127);
            this.DataDirectoryPathTextBox.Name = "DataDirectoryPathTextBox";
            this.DataDirectoryPathTextBox.Size = new System.Drawing.Size(483, 22);
            this.DataDirectoryPathTextBox.TabIndex = 5;
            // 
            // ExecuteCommandButton
            // 
            this.ExecuteCommandButton.Location = new System.Drawing.Point(257, 223);
            this.ExecuteCommandButton.Name = "ExecuteCommandButton";
            this.ExecuteCommandButton.Size = new System.Drawing.Size(163, 33);
            this.ExecuteCommandButton.TabIndex = 7;
            this.ExecuteCommandButton.Text = "Execute Command";
            this.ExecuteCommandButton.UseVisualStyleBackColor = true;
            this.ExecuteCommandButton.Click += new System.EventHandler(this.ExecuteCommandButton_Click);
            // 
            // AbortButton
            // 
            this.AbortButton.Location = new System.Drawing.Point(522, 223);
            this.AbortButton.Name = "AbortButton";
            this.AbortButton.Size = new System.Drawing.Size(152, 33);
            this.AbortButton.TabIndex = 8;
            this.AbortButton.Text = "Abort";
            this.AbortButton.UseVisualStyleBackColor = true;
            this.AbortButton.Click += new System.EventHandler(this.AbortButton_Click);
            // 
            // Identify4HumanTracking
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(783, 298);
            this.Controls.Add(this.AbortButton);
            this.Controls.Add(this.ExecuteCommandButton);
            this.Controls.Add(this.DataDirectoryPathTextBox);
            this.Controls.Add(this.ModelDirectoryPathTextBox);
            this.Controls.Add(this.ModelDirectoryPathButton);
            this.Controls.Add(this.DataDirectoryPathButton);
            this.Name = "Identify4HumanTracking";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Identify4HumanTracking";
            this.Load += new System.EventHandler(this.Identify4HumanTracking_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button DataDirectoryPathButton;
        private System.Windows.Forms.Button ModelDirectoryPathButton;
        private System.Windows.Forms.TextBox ModelDirectoryPathTextBox;
        private System.Windows.Forms.TextBox DataDirectoryPathTextBox;
        private System.Windows.Forms.Button ExecuteCommandButton;
        private System.Windows.Forms.Button AbortButton;
    }
}