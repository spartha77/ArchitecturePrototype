namespace HumanDetectionAndTracking
{
    partial class SkillExecuteInputForm
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
            this.ModelDirectoryPathButton.Location = new System.Drawing.Point(34, 67);
            this.ModelDirectoryPathButton.Margin = new System.Windows.Forms.Padding(2);
            this.ModelDirectoryPathButton.Name = "ModelDirectoryPathButton";
            this.ModelDirectoryPathButton.Size = new System.Drawing.Size(136, 32);
            this.ModelDirectoryPathButton.TabIndex = 0;
            this.ModelDirectoryPathButton.Text = "Model Directory Path";
            this.ModelDirectoryPathButton.UseVisualStyleBackColor = true;
            this.ModelDirectoryPathButton.Click += new System.EventHandler(this.ModelDirectoryPathButton_Click);
            // 
            // DataDirectoryPathButton
            // 
            this.DataDirectoryPathButton.Location = new System.Drawing.Point(34, 141);
            this.DataDirectoryPathButton.Margin = new System.Windows.Forms.Padding(2);
            this.DataDirectoryPathButton.Name = "DataDirectoryPathButton";
            this.DataDirectoryPathButton.Size = new System.Drawing.Size(136, 36);
            this.DataDirectoryPathButton.TabIndex = 1;
            this.DataDirectoryPathButton.Text = "Data Directory Path";
            this.DataDirectoryPathButton.UseVisualStyleBackColor = true;
            this.DataDirectoryPathButton.Click += new System.EventHandler(this.DataDirectoryPathButton_Click);
            // 
            // ModelDirectoryPathTextBox
            // 
            this.ModelDirectoryPathTextBox.Location = new System.Drawing.Point(206, 75);
            this.ModelDirectoryPathTextBox.Margin = new System.Windows.Forms.Padding(2);
            this.ModelDirectoryPathTextBox.Name = "ModelDirectoryPathTextBox";
            this.ModelDirectoryPathTextBox.Size = new System.Drawing.Size(356, 20);
            this.ModelDirectoryPathTextBox.TabIndex = 2;
            this.ModelDirectoryPathTextBox.TextChanged += new System.EventHandler(this.ModelDirectoryPathTextBox_TextChanged);
            // 
            // DataDirectoryPathTextBox
            // 
            this.DataDirectoryPathTextBox.Location = new System.Drawing.Point(206, 150);
            this.DataDirectoryPathTextBox.Margin = new System.Windows.Forms.Padding(2);
            this.DataDirectoryPathTextBox.Name = "DataDirectoryPathTextBox";
            this.DataDirectoryPathTextBox.Size = new System.Drawing.Size(356, 20);
            this.DataDirectoryPathTextBox.TabIndex = 3;
            this.DataDirectoryPathTextBox.TextChanged += new System.EventHandler(this.DataDirectoryPathTextBox_TextChanged);
            // 
            // ExecuteCommandButton
            // 
            this.ExecuteCommandButton.Location = new System.Drawing.Point(206, 237);
            this.ExecuteCommandButton.Margin = new System.Windows.Forms.Padding(2);
            this.ExecuteCommandButton.Name = "ExecuteCommandButton";
            this.ExecuteCommandButton.Size = new System.Drawing.Size(130, 37);
            this.ExecuteCommandButton.TabIndex = 4;
            this.ExecuteCommandButton.Text = "Execute";
            this.ExecuteCommandButton.UseVisualStyleBackColor = true;
            this.ExecuteCommandButton.Click += new System.EventHandler(this.ExecuteCommandButton_Click);
            // 
            // AbortButton
            // 
            this.AbortButton.Location = new System.Drawing.Point(393, 237);
            this.AbortButton.Margin = new System.Windows.Forms.Padding(2);
            this.AbortButton.Name = "AbortButton";
            this.AbortButton.Size = new System.Drawing.Size(131, 37);
            this.AbortButton.TabIndex = 5;
            this.AbortButton.Text = "Abort";
            this.AbortButton.UseVisualStyleBackColor = true;
            this.AbortButton.Click += new System.EventHandler(this.AbortButton_Click);
            // 
            // SkillIExecutenputForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(598, 317);
            this.Controls.Add(this.AbortButton);
            this.Controls.Add(this.ExecuteCommandButton);
            this.Controls.Add(this.DataDirectoryPathTextBox);
            this.Controls.Add(this.ModelDirectoryPathTextBox);
            this.Controls.Add(this.DataDirectoryPathButton);
            this.Controls.Add(this.ModelDirectoryPathButton);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "SkillIExecutenputForm";
            this.Text = "FaceIdentificationForm";
            this.Load += new System.EventHandler(this.SkillIExecutenputForm_Load);
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