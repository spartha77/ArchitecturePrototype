namespace HumanDetectionAndTracking
{
    partial class RegisterName4HumanTrackingForm
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
            this.ImageDirectoryPathButton = new System.Windows.Forms.Button();
            this.ExecuteCommandButton = new System.Windows.Forms.Button();
            this.AbortButton = new System.Windows.Forms.Button();
            this.ModelDirectoryPathTextBox = new System.Windows.Forms.TextBox();
            this.DataDirectoryPathTextBox = new System.Windows.Forms.TextBox();
            this.ImageDirectoryPathTextBox = new System.Windows.Forms.TextBox();
            this.RegisteredNameTextBox = new System.Windows.Forms.TextBox();
            this.groupBoxMode = new System.Windows.Forms.GroupBox();
            this.personNameRadioButton = new System.Windows.Forms.RadioButton();
            this.batchModeRadioButton = new System.Windows.Forms.RadioButton();
            this.OnlineRegistrationRadioButton = new System.Windows.Forms.RadioButton();
            this.RegisteredPersonName = new System.Windows.Forms.Label();
            this.groupBoxMode.SuspendLayout();
            this.SuspendLayout();
            // 
            // ModelDirectoryPathButton
            // 
            this.ModelDirectoryPathButton.Location = new System.Drawing.Point(27, 42);
            this.ModelDirectoryPathButton.Name = "ModelDirectoryPathButton";
            this.ModelDirectoryPathButton.Size = new System.Drawing.Size(114, 23);
            this.ModelDirectoryPathButton.TabIndex = 0;
            this.ModelDirectoryPathButton.Text = "Model Directory Path";
            this.ModelDirectoryPathButton.UseVisualStyleBackColor = true;
            this.ModelDirectoryPathButton.Click += new System.EventHandler(this.ModelDirectoryPathButton_Click);
            // 
            // DataDirectoryPathButton
            // 
            this.DataDirectoryPathButton.Location = new System.Drawing.Point(27, 91);
            this.DataDirectoryPathButton.Name = "DataDirectoryPathButton";
            this.DataDirectoryPathButton.Size = new System.Drawing.Size(114, 23);
            this.DataDirectoryPathButton.TabIndex = 1;
            this.DataDirectoryPathButton.Text = "Data Directory Path";
            this.DataDirectoryPathButton.UseVisualStyleBackColor = true;
            this.DataDirectoryPathButton.Click += new System.EventHandler(this.DataDirectoryPathButton_Click);
            // 
            // ImageDirectoryPathButton
            // 
            this.ImageDirectoryPathButton.Location = new System.Drawing.Point(27, 139);
            this.ImageDirectoryPathButton.Name = "ImageDirectoryPathButton";
            this.ImageDirectoryPathButton.Size = new System.Drawing.Size(114, 23);
            this.ImageDirectoryPathButton.TabIndex = 2;
            this.ImageDirectoryPathButton.Text = "Image Directory Path";
            this.ImageDirectoryPathButton.UseVisualStyleBackColor = true;
            this.ImageDirectoryPathButton.Click += new System.EventHandler(this.ImageDirectoryPathButton_Click);
            // 
            // ExecuteCommandButton
            // 
            this.ExecuteCommandButton.Location = new System.Drawing.Point(262, 341);
            this.ExecuteCommandButton.Name = "ExecuteCommandButton";
            this.ExecuteCommandButton.Size = new System.Drawing.Size(106, 23);
            this.ExecuteCommandButton.TabIndex = 3;
            this.ExecuteCommandButton.Text = "Execute";
            this.ExecuteCommandButton.UseVisualStyleBackColor = true;
            this.ExecuteCommandButton.Click += new System.EventHandler(this.ExecuteCommandButton_Click);
            // 
            // AbortButton
            // 
            this.AbortButton.Location = new System.Drawing.Point(445, 341);
            this.AbortButton.Name = "AbortButton";
            this.AbortButton.Size = new System.Drawing.Size(106, 23);
            this.AbortButton.TabIndex = 4;
            this.AbortButton.Text = "Abort";
            this.AbortButton.UseVisualStyleBackColor = true;
            this.AbortButton.Click += new System.EventHandler(this.AbortButton_Click);
            // 
            // ModelDirectoryPathTextBox
            // 
            this.ModelDirectoryPathTextBox.HideSelection = false;
            this.ModelDirectoryPathTextBox.Location = new System.Drawing.Point(158, 45);
            this.ModelDirectoryPathTextBox.Name = "ModelDirectoryPathTextBox";
            this.ModelDirectoryPathTextBox.Size = new System.Drawing.Size(390, 20);
            this.ModelDirectoryPathTextBox.TabIndex = 5;
            this.ModelDirectoryPathTextBox.TextChanged += new System.EventHandler(this.ModelDirectoryPathTextBox_TextChanged);
            // 
            // DataDirectoryPathTextBox
            // 
            this.DataDirectoryPathTextBox.Location = new System.Drawing.Point(158, 93);
            this.DataDirectoryPathTextBox.Name = "DataDirectoryPathTextBox";
            this.DataDirectoryPathTextBox.Size = new System.Drawing.Size(390, 20);
            this.DataDirectoryPathTextBox.TabIndex = 6;
            this.DataDirectoryPathTextBox.TextChanged += new System.EventHandler(this.DataDirectoryPathTextBox_TextChanged);
            // 
            // ImageDirectoryPathTextBox
            // 
            this.ImageDirectoryPathTextBox.Location = new System.Drawing.Point(158, 142);
            this.ImageDirectoryPathTextBox.Name = "ImageDirectoryPathTextBox";
            this.ImageDirectoryPathTextBox.Size = new System.Drawing.Size(390, 20);
            this.ImageDirectoryPathTextBox.TabIndex = 7;
            this.ImageDirectoryPathTextBox.TextChanged += new System.EventHandler(this.ImageDirectoryPathTextBox_TextChanged);
            // 
            // RegisteredNameTextBox
            // 
            this.RegisteredNameTextBox.Location = new System.Drawing.Point(189, 74);
            this.RegisteredNameTextBox.Name = "RegisteredNameTextBox";
            this.RegisteredNameTextBox.Size = new System.Drawing.Size(152, 20);
            this.RegisteredNameTextBox.TabIndex = 9;
            this.RegisteredNameTextBox.TextChanged += new System.EventHandler(this.RegisteredNameTextBox_TextChanged);
            // 
            // groupBoxMode
            // 
            this.groupBoxMode.Controls.Add(this.RegisteredPersonName);
            this.groupBoxMode.Controls.Add(this.OnlineRegistrationRadioButton);
            this.groupBoxMode.Controls.Add(this.RegisteredNameTextBox);
            this.groupBoxMode.Controls.Add(this.personNameRadioButton);
            this.groupBoxMode.Controls.Add(this.batchModeRadioButton);
            this.groupBoxMode.Location = new System.Drawing.Point(27, 202);
            this.groupBoxMode.Margin = new System.Windows.Forms.Padding(2);
            this.groupBoxMode.Name = "groupBoxMode";
            this.groupBoxMode.Padding = new System.Windows.Forms.Padding(2);
            this.groupBoxMode.Size = new System.Drawing.Size(524, 102);
            this.groupBoxMode.TabIndex = 10;
            this.groupBoxMode.TabStop = false;
            this.groupBoxMode.Text = "Mode";
            this.groupBoxMode.Enter += new System.EventHandler(this.groupBoxMode_Enter);
            // 
            // personNameRadioButton
            // 
            this.personNameRadioButton.AutoSize = true;
            this.personNameRadioButton.Checked = true;
            this.personNameRadioButton.Location = new System.Drawing.Point(189, 41);
            this.personNameRadioButton.Margin = new System.Windows.Forms.Padding(2);
            this.personNameRadioButton.Name = "personNameRadioButton";
            this.personNameRadioButton.Size = new System.Drawing.Size(89, 17);
            this.personNameRadioButton.TabIndex = 1;
            this.personNameRadioButton.Text = "Person Name";
            this.personNameRadioButton.UseVisualStyleBackColor = true;
            this.personNameRadioButton.CheckedChanged += new System.EventHandler(this.personNameRadioButton_CheckedChanged);
            // 
            // batchModeRadioButton
            // 
            this.batchModeRadioButton.AutoSize = true;
            this.batchModeRadioButton.ForeColor = System.Drawing.SystemColors.ControlText;
            this.batchModeRadioButton.Location = new System.Drawing.Point(32, 42);
            this.batchModeRadioButton.Margin = new System.Windows.Forms.Padding(2);
            this.batchModeRadioButton.Name = "batchModeRadioButton";
            this.batchModeRadioButton.Size = new System.Drawing.Size(83, 17);
            this.batchModeRadioButton.TabIndex = 0;
            this.batchModeRadioButton.Text = "Batch Mode";
            this.batchModeRadioButton.UseVisualStyleBackColor = true;
            this.batchModeRadioButton.CheckedChanged += new System.EventHandler(this.batchModeRadioButton_CheckedChanged);
            // 
            // OnlineRegistrationRadioButton
            // 
            this.OnlineRegistrationRadioButton.AutoSize = true;
            this.OnlineRegistrationRadioButton.Location = new System.Drawing.Point(388, 41);
            this.OnlineRegistrationRadioButton.Margin = new System.Windows.Forms.Padding(2);
            this.OnlineRegistrationRadioButton.Name = "OnlineRegistrationRadioButton";
            this.OnlineRegistrationRadioButton.Size = new System.Drawing.Size(55, 17);
            this.OnlineRegistrationRadioButton.TabIndex = 10;
            this.OnlineRegistrationRadioButton.Text = "Online";
            this.OnlineRegistrationRadioButton.UseVisualStyleBackColor = true;
            this.OnlineRegistrationRadioButton.CheckedChanged += new System.EventHandler(this.OnlineRegistrationRadioButton_CheckedChanged);
            // 
            // RegisteredPersonName
            // 
            this.RegisteredPersonName.Location = new System.Drawing.Point(29, 77);
            this.RegisteredPersonName.Name = "RegisteredPersonName";
            this.RegisteredPersonName.Size = new System.Drawing.Size(100, 23);
            this.RegisteredPersonName.TabIndex = 11;
            this.RegisteredPersonName.Text = "Registered Person Name";
            this.RegisteredPersonName.Click += new System.EventHandler(this.label1_Click);
            // 
            // RegisterName4HumanTrackingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(576, 376);
            this.Controls.Add(this.groupBoxMode);
            this.Controls.Add(this.ImageDirectoryPathTextBox);
            this.Controls.Add(this.DataDirectoryPathTextBox);
            this.Controls.Add(this.ModelDirectoryPathTextBox);
            this.Controls.Add(this.AbortButton);
            this.Controls.Add(this.ExecuteCommandButton);
            this.Controls.Add(this.ImageDirectoryPathButton);
            this.Controls.Add(this.DataDirectoryPathButton);
            this.Controls.Add(this.ModelDirectoryPathButton);
            this.Name = "RegisterName4HumanTrackingForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Skill : Face Registration";
            this.Load += new System.EventHandler(this.RegisterName4HumanTracking_Load);
            this.groupBoxMode.ResumeLayout(false);
            this.groupBoxMode.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ModelDirectoryPathButton;
        private System.Windows.Forms.Button DataDirectoryPathButton;
        private System.Windows.Forms.Button ImageDirectoryPathButton;
        private System.Windows.Forms.Button ExecuteCommandButton;
        private System.Windows.Forms.Button AbortButton;
        private System.Windows.Forms.TextBox ModelDirectoryPathTextBox;
        private System.Windows.Forms.TextBox DataDirectoryPathTextBox;
        private System.Windows.Forms.TextBox ImageDirectoryPathTextBox;
        private System.Windows.Forms.TextBox RegisteredNameTextBox;
        private System.Windows.Forms.GroupBox groupBoxMode;
        private System.Windows.Forms.RadioButton personNameRadioButton;
        private System.Windows.Forms.RadioButton batchModeRadioButton;
        private System.Windows.Forms.RadioButton OnlineRegistrationRadioButton;
        private System.Windows.Forms.Label RegisteredPersonName;
    }
}