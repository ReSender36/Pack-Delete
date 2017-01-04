// ---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <winbase.h>
#include <shellapi.h>
#include <systdate.h>
#pragma hdrstop

#include "PackAndDelete_mod.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPackAndDelete_Form *PackAndDelete_Form;
String pr[10]; // [10] ;
String prf[10][2];

// short packdays, deldays ;
// ---------------------------------------------------------------------------
__fastcall TPackAndDelete_Form::TPackAndDelete_Form(TComponent* Owner)
	: TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool chk_file(FILE fc) {

}

// ---------------------------------------------------------------------------
void conv_date(TDateTime *op1, String *dts, bool direct) {
	// переменная direct указывает на конечный формат преобразования даты времени
	// true к виду: 2013-09-21
	// false - 20130921
	unsigned short Year;
	unsigned short Month;
	unsigned short Day;
	TDateTime o;

	op1->DecodeDate(&Year, &Month, &Day);

	String ys = String(Year);
	String ms = String(Month);
	String ds = String(Day);

	switch (Month) {
	case 1:
		ms = String("0" + ms);
		break;
	case 2:
		ms = String("0" + ms);
		break;
	case 3:
		ms = String("0" + ms);
		break;
	case 4:
		ms = String("0" + ms);
		break;
	case 5:
		ms = String("0" + ms);
		break;
	case 6:
		ms = String("0" + ms);
		break;
	case 7:
		ms = String("0" + ms);
		break;
	case 8:
		ms = String("0" + ms);
		break;
	case 9:
		ms = String("0" + ms);
		break;
	default:
		ms;
	}
	switch (Day) {
	case 1:
		ds = String("0" + ds);
		break;
	case 2:
		ds = String("0" + ds);
		break;
	case 3:
		ds = String("0" + ds);
		break;
	case 4:
		ds = String("0" + ds);
		break;
	case 5:
		ds = String("0" + ds);
		break;
	case 6:
		ds = String("0" + ds);
		break;
	case 7:
		ds = String("0" + ds);
		break;
	case 8:
		ds = String("0" + ds);
		break;
	case 9:
		ds = String("0" + ds);
		break;
	default:
		ds;
	}
	if (direct)
		* dts = String(ys + "-" + ms + "-" + ds);
	else
		*dts = String(ys + ms + ds);

}

// ---------------------------------------------------------------------------
void sort_mas() {
	for (short i = 0; i < 100; i++) {
		if ("" == pr[i]) {
			i--;
			continue;
		}
		for (short j = i + 1; j < 100; j++) {
			if ("" == pr[j]) {
				pr[j] = "0";
				j--;
				continue;
			}
			if (StrToInt(pr[i]) > StrToInt(pr[j])) {
				if ("" == pr[i])
					continue;

				short c = StrToInt(pr[i]);
				pr[i] = pr[j];
				pr[j] = c;
			}
		}
	}
}

// ---------------------------------------------------------------------------
short exist(short df_c) {
	for (short j = 0; j < 10; j++)
		if (pr[j] == df_c)
			return j;
	return 1000;
}
// ---------------------------------------------------------------------------
TDateTime FileTimeToDateTime(FILETIME *lpftime) {
	FILETIME localfiletime;
	SYSTEMTIME systime;
	TDateTime ConvDateTime;
	FileTimeToLocalFileTime(lpftime, &localfiletime);
	FileTimeToSystemTime(&localfiletime, &systime);
	try {
		ConvDateTime = (TDateTime(systime.wYear, systime.wMonth, systime.wDay) +
			TDateTime(systime.wHour, systime.wMinute, systime.wSecond,
			systime.wMilliseconds));
	}
	catch (...) {
		// systime = "00000000000000000". ;
		ConvDateTime = (TDateTime(1980, 01, 01) + TDateTime(23, 59, 59, 000));
	}
	if (0 == &systime)
		ConvDateTime = (TDateTime(1980, 01, 01) + TDateTime(23, 59, 59, 000));

	return ConvDateTime;
}

// ---------------------------------------------------------------------------
int pack_files(short pd, String path_pack, String mask_files) {
	TDateTime la;
	TDateTime StartDateTime = TDateTime::CurrentDateTime();
	short datefile;
	short df_curr = 0;
	int cnt_f = 0;
	int files_pack = 0;
	short cnt_mas = 0;
	String la_str = "";
	String la_strOld = "";
	String f_nameIn;
	String f_nameArch;
	String arch_opt = "a -ep -IBCK -df ";
	WideString ao;

	FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
	HANDLE hFile;
	PackAndDelete_Form->FileListBox1->Directory = path_pack;
	PackAndDelete_Form->FileListBox1->Mask = mask_files;
	PackAndDelete_Form->FileListBox1->Update();
	PackAndDelete_Form->ProgressBar1->Min = 1;
	PackAndDelete_Form->ProgressBar1->Max =
		PackAndDelete_Form->FileListBox1->Items->Count;
	for (short j = 0; j < 5; j++) {
		if (PackAndDelete_Form->FileListBox1->Items->Count > 0) {
			for (int i = 0;
			i < PackAndDelete_Form->FileListBox1->Items->Count; i++) {
				hFile = (HANDLE)FileOpen
					(PackAndDelete_Form->FileListBox1->Items->Strings[i],
					fmOpenRead);
				GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime,
					&ftLastWriteTime);
				// la = FileTimeToDateTime(&ftCreationTime) ;
				la = FileTimeToDateTime(&ftLastWriteTime);
				FileClose((int) hFile);
				df_curr = int(StartDateTime - la);
				if (pd <= df_curr) {
					conv_date(&la, &la_str, true);
					f_nameArch = la_str + ".rar";
					f_nameIn = PackAndDelete_Form->FileListBox1->Directory +
						"\\" + PackAndDelete_Form->FileListBox1->Items->
						Strings[i];
					ao = arch_opt + f_nameArch + " " + f_nameIn;
					ShellExecuteA(NULL, "open", "WinRAR.exe",
						AnsiString(ao).c_str(), NULL, SW_SHOWNORMAL);

					for (int z = 0; z < 15000000; z++) {
					}
					files_pack++;
					PackAndDelete_Form->ProgressBar1->Position = i;
					PackAndDelete_Form->FileListBox1->Update();
				}
			}
			for (int z = 0; z < 5000000; z++) {
			}
			PackAndDelete_Form->FileListBox1->Update();
		}
		for (int z = 0; z < 50000000; z++) {
		}
		PackAndDelete_Form->FileListBox1->Update();
		PackAndDelete_Form->ProgressBar1->Max =
			PackAndDelete_Form->FileListBox1->Items->Count;
	}
	return files_pack;
}

// ---------------------------------------------------------------------------
int delete_files(short dd, String path_del, String mask_files) {
	TDateTime la;
	TDateTime StartDateTime = TDateTime::CurrentDateTime();
	HANDLE hFile;
	short datefile;
	int df_curr = 0;
	int cnt_f = 0;
	int files_del = 0;
	WideString ao;
	WideString f_nameIn;
	FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;

	PackAndDelete_Form->FileListBox1->Mask = mask_files;
	PackAndDelete_Form->FileListBox1->Directory = path_del;
	PackAndDelete_Form->FileListBox1->Update();

	for (int i = 0; i < PackAndDelete_Form->FileListBox1->Items->Count; i++) {
		hFile = (HANDLE)FileOpen(PackAndDelete_Form->FileListBox1->Items->Strings[i], fmOpenRead);
		GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime,&ftLastWriteTime);
		la = FileTimeToDateTime(&ftLastWriteTime);
		FileClose((int) hFile);
		df_curr = int(StartDateTime - la);

		if (dd <= df_curr) {
			f_nameIn = PackAndDelete_Form->FileListBox1->Directory + "\\" +
				PackAndDelete_Form->FileListBox1->Items->Strings[i];
			remove(AnsiString(f_nameIn).c_str());
			files_del++;
		}
	}
	PackAndDelete_Form->FileListBox1->Update();
	return files_del;
}

// ---------------------------------------------------------------------------
void write_log(String pkl, int fp, int fd, TDateTime fdt) {
	String CurrDateTime_str;
	TDateTime CurrDateTime = TDateTime::CurrentDate();
	conv_date(&CurrDateTime, &CurrDateTime_str, false);
	PackAndDelete_Form->ADOCommand1->CommandText = String("insert into PackAndDelete_Stats (act_date, client, packed_files,deleted_files) \
	values ('" + CurrDateTime_str + "', '" + pkl + "', " + IntToStr(fp) + ", " +
		IntToStr(fd) + ") ;");
	PackAndDelete_Form->ADOCommand1->Execute();
}

// ---------------------------------------------------------------------------
void __fastcall TPackAndDelete_Form::Button1Click(TObject *Sender) {
	TDateTime la;
	TDateTime StartDateTime = TDateTime::CurrentDateTime();
	short datefile;
	short df_curr = 0;
	short archday = 0;
	int cnt_f = 0;
	short cnt_mas = 0;
	String la_str = "";
	String la_strOld = "";
	String f_nameIn;
	String f_nameArch;
	String arch_opt = "a -ep -IBCK -df ";
	WideString ao;

	FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
	HANDLE hFile = (HANDLE)FileOpen("c:\\mini-agent.txt", fmOpenRead);
	GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
	AnsiString FileInfo = "FileName: c:\\123.rar";
	FileInfo += "\nCreation Time:" + FormatDateTime("c",
		FileTimeToDateTime(&ftCreationTime));
	FileInfo += "\nLast Access Time:" + FormatDateTime("c",
		FileTimeToDateTime(&ftLastAccessTime));
	FileInfo += "\nLast Write Time:" + FormatDateTime("c",
		FileTimeToDateTime(&ftLastWriteTime));
	la = FileTimeToDateTime(&ftLastWriteTime);
	// Label1->Caption=FileInfo;
	FileClose((int) hFile);
	// Edit1->Text = int(StartDateTime - la) ;
	datefile = 0;
	FileListBox1->Directory = "C:\\temp\\Exchange\\pack\\";
	FileListBox1->Mask = "*.xml";
	FileListBox1->Update();
	// Edit1->Text = String(FileListBox1->Items->Count) ;
	ProgressBar1->Min = 1;
	ProgressBar1->Max = FileListBox1->Items->Count;
	for (short j = 0; j < 5; j++) {
		if (FileListBox1->Items->Count > 0) {
			for (int i = 0; i < FileListBox1->Items->Count; i++) {
				hFile = (HANDLE)FileOpen(FileListBox1->Items->Strings[i],
					fmOpenRead);
				GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime,
					&ftLastWriteTime);
				la = FileTimeToDateTime(&ftLastWriteTime);
				FileClose((int) hFile);
				df_curr = int(StartDateTime - la);

				if (archday <= df_curr) {
					conv_date(&la, &la_str, true);
					// if (la_strOld == la_str)
					// {
					f_nameArch = la_str + ".rar";
					// f_nameIn = FileListBox1->Directory + "\\123.out" ;
					f_nameIn = FileListBox1->Directory + "\\" +
						FileListBox1->Items->Strings[i];
					ao = arch_opt + f_nameArch + " " + f_nameIn;
					ShellExecuteA(Handle, "open",
						"C:\\Program Files (x86)\\WinRAR\\WinRAR.exe",
						AnsiString(ao).c_str(), NULL, SW_SHOWNORMAL);

					for (int z = 0; z < 15000000; z++) {
					}
					ProgressBar1->Position = i;
					FileListBox1->Update();
					// }
					// else
					// {
					// la_strOld = la_str ;
					// }
				}
			}
			for (int z = 0; z < 5000000; z++) {
			}
			FileListBox1->Update();
			// Edit3->Text = String(j) ;
		}
		// Edit3->Text = String(FileListBox1->Items->Count) ;
		for (int z = 0; z < 50000000; z++) {
		}
		FileListBox1->Update();
		ProgressBar1->Max = FileListBox1->Items->Count;
		// Label1->Caption = "Проход " + IntToStr(j) ;
	}
	// Edit2->Text = String(FileListBox1->Items->Count) ;

	/* if (datefile != df_curr && 1000 == exist(df_curr))
	 {
	 pr[cnt_mas] = IntToStr(df_curr) ;
	 cnt_mas++ ;
	 datefile = df_curr ;
	 df_curr = 0 ;
	 }
	 if (1000 < exist(df_curr))
	 prf[10]
	 }
	 //		else cnt_f++ ;
	 }
	 //	sort_mas() ;
	 //	for (short j = 0; j < 10; j++) Edit1->Text = pr[j] + " " ; */
}

// ---------------------------------------------------------------------------
void __fastcall TPackAndDelete_Form::Button2Click(TObject *Sender) {
	short deldays;

	TDateTime la;
	TDateTime StartDateTime = TDateTime::CurrentDateTime();
	short datefile;
	int df_curr = 0;
	int cnt_f = 0;
	WideString ao;
	WideString f_nameIn;
	// C:\\temp\\Exchange\\pack\\
	FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;

	deldays = 21;

	// Edit4->Text = String(deldays) ;

	// FileListBox1->Mask = "*.rar" ;
	FileListBox1->Mask = "*.xml";
	// FileListBox1->Directory = "C:\\temp\\Exchange\\pack\\" ;
	FileListBox1->Directory = "\\\\mskcoskl\\exchange\\Верный\\arc\\";
	FileListBox1->Update();
	// Edit4->Text = FileListBox1->Items->Count ;
	/*
	 HANDLE hFile ;

	 for(int i = 0; i < FileListBox1->Items->Count; i++)
	 {
	 hFile = (HANDLE)FileOpen(FileListBox1->Items->Strings[i],fmOpenRead);
	 GetFileTime(hFile,&ftCreationTime,&ftLastAccessTime,&ftLastWriteTime);
	 la = FileTimeToDateTime(&ftLastWriteTime) ;
	 FileClose((int) hFile);
	 df_curr = int(StartDateTime - la) ;

	 if (deldays <= df_curr)
	 {
	 f_nameIn = FileListBox1->Directory + "\\" + FileListBox1->Items->Strings[i] ;
	 remove(AnsiString(f_nameIn).c_str()) ;
	 }
	 }
	 FileListBox1->Update() ; */
}
// ---------------------------------------------------------------------------

void __fastcall TPackAndDelete_Form::Button3Click(TObject *Sender) {
	/*
	 PackAndDelete_Form->ADOConnection1->Connected ;
	 String path, mask, pokl ;
	 short packdays, deldays ;
	 int files_packed, files_deleted ;
	 TDateTime DateTime_from = TDateTime::CurrentDateTime().DateTimeString() ;


	 ADOQuery1->Active = false ;
	 ADOQuery1->SQL->Text = String("select value from options o where option_name = 'day_to_arch'") ;
	 ADOQuery1->Active = true ;
	 packdays = ADOQuery1->FieldByName("value")->AsInteger ;

	 ADOQuery1->Active = false ;
	 ADOQuery1->SQL->Text = String("select value from options o where option_name = 'day_to_delete'") ;
	 ADOQuery1->Active = true ;
	 deldays = ADOQuery1->FieldByName("value")->AsInteger ;

	 ADOQuery1->Active = false ;
	 ADOQuery1->SQL->Text = String("SELECT S.SP2503 AS pokl_id, s1.DESCR AS pokl, S.SP2504 AS arch_path, S.SP3250 as file_type \
	 FROM SC2510 S \
	 INNER JOIN SC59 S1 ON S1.ID = S.SP2503 \
	 WHERE S.SP3250 = 'xml' ;") ;
	 ADOQuery1->Active = true ;
	 ADOQuery1->First() ;
	 while(!ADOQuery1->Eof)
	 {
	 //		path = "C:\\temp\\Exchange\\3PL_arch\\Старбакс\\" ;
	 path = ADOQuery1->FieldByName("arch_path")->AsString ;
	 mask = "*." + ADOQuery1->FieldByName("file_type")->AsString ;
	 pokl = ADOQuery1->FieldByName("pokl")->AsString ;
	 files_packed = pack_files(packdays, path, mask) ;
	 mask = "*.rar" ;
	 files_deleted = delete_files(deldays, path, mask) ;
	 write_log(pokl, files_packed, files_deleted, DateTime_from) ;
	 ADOQuery1->Next() ;
	 }
	 */
	// FILETIME ftCreationTime,ftLastAccessTime,ftLastWriteTime;
	// unsigned long f_size ;
	/*
	 unsigned long f_size ;
	 HANDLE hFile=(HANDLE)FileOpen("c:\\U0002330.dbf",fmOpenRead);
	 GetFileSize(hFile,&f_size);
	 */
	FILE *fin;
	// fin = fopen("c:\\temp\\Backups\\Note_Dell_DocsMSKNB0036(1).tib", "rb");
	fin = fopen("C:\\123.log", "rb");
	unsigned long int f_size;

	fseek(fin, 0, SEEK_END);
	f_size = ftell(fin);
	// fseek(fin, 0, SEEK_SET);

	GetLogicalDrives();

	_ULARGE_INTEGER free_b, tot_b, totFree_b;
	// unsigned long int free_b;

 //	AnsiString dsk = DriveComboBox1->Items->Text ; //"C:";
	AnsiString dsk = "C:";
	Edit1->Text = dsk ;
	// GetDiskFreeSpaceEx("Ваш диск", &free, NULL, NULL);
	GetDiskFreeSpaceExA(dsk.c_str(), &free_b, &tot_b, &totFree_b);
	// std::cout << free.QuadPart << std::endl; // свободное место в байтах

	// Edit1->Text = UnicodeString(f_size) ;
	Edit1->Text = ((free_b.QuadPart / 1024) / 1024) / 1024 ;
	Edit2->Text = ((tot_b.QuadPart / 1024) / 1024) / 1024 ;
	Edit3->Text = totFree_b.QuadPart / 1024;
	Edit4->Text = (tot_b.QuadPart - free_b.QuadPart) / 1024 ;
}
// ---------------------------------------------------------------------------

void __fastcall TPackAndDelete_Form::Timer1Timer(TObject *Sender) {
	/*
	 PackAndDelete_Form->ADOConnection1->Connected ;
	 String path, mask, pokl ;
	 short packdays, deldays ;
	 int files_packed, files_deleted ;
	 TDateTime DateTime_from = TDateTime::CurrentDateTime().DateTimeString() ;


	 ADOQuery1->Active = false ;
	 ADOQuery1->SQL->Text = String("select value from options o where option_name = 'day_to_arch'") ;
	 ADOQuery1->Active = true ;
	 packdays = ADOQuery1->FieldByName("value")->AsInteger ;

	 ADOQuery1->Active = false ;
	 ADOQuery1->SQL->Text = String("select value from options o where option_name = 'day_to_delete'") ;
	 ADOQuery1->Active = true ;
	 deldays = ADOQuery1->FieldByName("value")->AsInteger ;

	 ADOQuery1->Active = false ;
	 ADOQuery1->SQL->Text = String("SELECT S.SP2503 AS pokl_id, s1.DESCR AS pokl, S.SP2504 AS arch_path, S.SP3250 as file_type \
	 FROM SC2510 S \
	 INNER JOIN SC59 S1 ON S1.ID = S.SP2503 \
	 WHERE S.SP3250 = 'xml' ;") ;
	 ADOQuery1->Active = true ;
	 ADOQuery1->First() ;
	 while(!ADOQuery1->Eof)
	 {
	 //		path = "C:\\temp\\Exchange\\3PL_arch\\Старбакс\\" ;
	 path = ADOQuery1->FieldByName("arch_path")->AsString ;
	 mask = "*." + ADOQuery1->FieldByName("file_type")->AsString ;
	 pokl = ADOQuery1->FieldByName("pokl")->AsString ;
	 files_packed = pack_files(packdays, path, mask) ;
	 mask = "*.rar" ;
	 files_deleted = delete_files(deldays, path, mask) ;
	 write_log(pokl, files_packed, files_deleted, DateTime_from) ;
	 ADOQuery1->Next() ;
	 }
	 */
}
// ---------------------------------------------------------------------------
