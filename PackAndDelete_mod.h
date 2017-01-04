//---------------------------------------------------------------------------

#ifndef PackAndDelete_modH
#define PackAndDelete_modH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPackAndDelete_Form : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TFileListBox *FileListBox1;
	TButton *Button2;
	TProgressBar *ProgressBar1;
	TADOConnection *ADOConnection1;
	TADOQuery *ADOQuery1;
	TADOCommand *ADOCommand1;
	TButton *Button3;
	TTimer *Timer1;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TDriveComboBox *DriveComboBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TPackAndDelete_Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPackAndDelete_Form *PackAndDelete_Form;
//---------------------------------------------------------------------------
#endif
