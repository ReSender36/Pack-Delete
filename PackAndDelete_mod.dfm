object PackAndDelete_Form: TPackAndDelete_Form
  Left = 0
  Top = 0
  Caption = #1092#1086#1088#1084#1072' '#1088#1072#1073#1086#1090#1099' '#1089' '#1092#1072#1081#1083#1072#1084#1080
  ClientHeight = 384
  ClientWidth = 225
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 5
    Top = 280
    Width = 81
    Height = 13
    Caption = #1057#1074#1086#1073#1086#1076#1085#1086', '#1073#1072#1081#1090
  end
  object Label2: TLabel
    Left = 5
    Top = 307
    Width = 77
    Height = 13
    Caption = #1053#1072' '#1076#1080#1089#1082#1077', '#1073#1072#1081#1090
  end
  object Label3: TLabel
    Left = 5
    Top = 334
    Width = 89
    Height = 13
    Caption = #1042#1089#1077#1075#1086' '#1089#1074#1086#1073'., '#1073#1072#1081#1090
  end
  object Label4: TLabel
    Left = 5
    Top = 358
    Width = 91
    Height = 13
    Caption = #1056#1072#1079#1085#1080#1094#1072' 2-1, '#1073#1072#1081#1090
  end
  object Button1: TButton
    Left = 124
    Top = 207
    Width = 97
    Height = 25
    Caption = #1040#1088#1093#1080#1074#1080#1088#1086#1074#1072#1085#1080#1077
    TabOrder = 0
    OnClick = Button1Click
  end
  object FileListBox1: TFileListBox
    Left = 8
    Top = 8
    Width = 213
    Height = 162
    ItemHeight = 13
    TabOrder = 1
  end
  object Button2: TButton
    Left = 124
    Top = 240
    Width = 97
    Height = 25
    Caption = #1059#1076#1072#1083#1077#1085#1080#1077
    TabOrder = 2
    OnClick = Button2Click
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 176
    Width = 213
    Height = 17
    Step = 1
    TabOrder = 3
  end
  object Button3: TButton
    Left = 8
    Top = 207
    Width = 89
    Height = 25
    Caption = #1048#1085#1092#1072' '#1087#1086' '#1076#1080#1089#1082#1091
    TabOrder = 4
    OnClick = Button3Click
  end
  object Edit1: TEdit
    Left = 100
    Top = 277
    Width = 121
    Height = 21
    TabOrder = 5
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 100
    Top = 304
    Width = 121
    Height = 21
    TabOrder = 6
    Text = 'Edit2'
  end
  object Edit3: TEdit
    Left = 100
    Top = 331
    Width = 121
    Height = 21
    TabOrder = 7
    Text = 'Edit3'
  end
  object Edit4: TEdit
    Left = 100
    Top = 355
    Width = 121
    Height = 21
    TabOrder = 8
    Text = 'Edit4'
  end
  object DriveComboBox1: TDriveComboBox
    Left = 8
    Top = 238
    Width = 89
    Height = 19
    TabOrder = 9
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initi' +
      'al Catalog=SKLADcopy;Data Source=mskcoskl;Use Procedure for Prep' +
      'are=1;Auto Translate=True;Packet Size=4096;Workstation ID=MSKCOW' +
      '18609;Use Encryption for Data=False;Tag with column collation wh' +
      'en possible=False;'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 24
    Top = 16
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 16
    Top = 64
  end
  object ADOCommand1: TADOCommand
    Connection = ADOConnection1
    Parameters = <>
    Left = 16
    Top = 120
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 128
    Top = 24
  end
end
