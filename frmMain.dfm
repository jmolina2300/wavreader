object Form1: TForm1
  Left = 309
  Top = 118
  Width = 400
  Height = 400
  Caption = 'Wavreader'
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 400
  Font.Charset = EASTEUROPE_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 14
  object Splitter1: TSplitter
    Left = 0
    Top = 201
    Width = 392
    Height = 1
    Cursor = crVSplit
    Align = alTop
  end
  object DBChart1: TDBChart
    Left = 0
    Top = 202
    Width = 392
    Height = 167
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'TDBChart')
    Title.Visible = False
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 32768
    LeftAxis.Minimum = -32768
    Legend.Visible = False
    View3D = False
    Align = alClient
    BevelOuter = bvLowered
    TabOrder = 0
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 392
    Height = 201
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 44
      Height = 14
      Caption = 'WAV File'
    end
    object Label2: TLabel
      Left = 16
      Top = 64
      Width = 32
      Height = 14
      Caption = 'Details'
    end
    object Button1: TButton
      Left = 272
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Open'
      TabOrder = 0
      OnClick = Button1Click
    end
    object tbxFileInfo: TRichEdit
      Left = 64
      Top = 64
      Width = 281
      Height = 129
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      WordWrap = False
    end
    object tbxFileName: TEdit
      Left = 64
      Top = 16
      Width = 201
      Height = 22
      TabOrder = 2
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 352
    Top = 16
  end
end
