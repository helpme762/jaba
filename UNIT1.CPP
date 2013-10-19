//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Select(int pos, int level){

//	level - позиция переборного номера в варианте, уровень рекурсии
// pos -
// при достижении последнего уровня рекурсии оно должно записать
// весь массив в файл и выйти
	int i,n,sum;

	for (i=pos+1; i<Number; i++){
		SortNdx[level]=i;
		if(level){
			Select(i, level-1);
			}
		else{
// имеем в SortNdx[] полный набор комбинаций теперь надо подсчитать для него Mass
			sum=0;
			for (n=0; n<NowNumber; n++)
				sum+=Var[ SortNdx[n] ];

			if (sum>InterpMass && sum<=Mass){
				InterpMass=sum;
				InterpNum=NowNumber;
				for (n=0; n<NowNumber; n++)
					MaxNdx[n]=SortNdx[n];
				}
			}
		}


}

//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject *Sender)
{
	Number=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Sorten(void)
{
	int n,temp;
	bool flag;
	// сортировка по возрастанию
	do{
		flag=false;
		for (n=0 ; n<Number-1 ; n++)
			if (SortNdx[n] > SortNdx[n+1]){
				temp=SortNdx[n+1];
				SortNdx[n+1]=SortNdx[n];
				SortNdx[n]=temp;
				flag=true;
				}
		}while (flag);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::EditMassKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
	if(Key==13) BitBtnGoClick(Sender);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::StringGrid1KeyPress(TObject *Sender, char &Key)
{
	if(Key==13){
		AnsiString S=StringGrid1->Cells[2][StringGrid1->RowCount-1];
		StringGrid1->Cells[0][StringGrid1->RowCount-1]=IntToStr(Number+1);
		if ( S.Length() && StrToInt(S) ){

			Var[Number]=SortNdx[Number]=StrToInt(S);
			Number++;

			StringGrid1->RowCount++;
			StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();

			TGridRect myRect;
			myRect.Left = 2;
			myRect.Top = Number+1;
			myRect.Right = 2;
			myRect.Bottom = Number+1;
			StringGrid1->Selection = myRect;
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtnGoClick(TObject *Sender)
{
	Mass=StrToInt(EditMass->Text);
	Sorten();
	int n,sum=0;
	MaxN=MinN=0;

	for (n=0; n<Number; n++){
		if ( sum+SortNdx[n]>Mass ) break;
		sum+=SortNdx[n];
		MaxN++;
		}
	sum=0;
	for (n=Number-1; n>=0; n--){
		if ( sum+SortNdx[n]>Mass ) continue;
		sum+=SortNdx[n];
		MinN++;
		}

	LabelMax->Caption=MaxN;
	LabelMin->Caption=MinN;

	InterpMass=0;
	for (n=MinN; n<=MaxN; n++){
		NowNumber=n;
		Select(-1, n-1);
		}

	LabelMass->Caption=InterpMass;

	for(n=0; n<InterpNum; n++){
//		ListBox1->Selected[ MaxNdx[n] ]=true;
		StringGrid1->Cells[3][MaxNdx[n]+1]="*";
		}
//   Number=0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtnClearClick(TObject *Sender)
{
	Number=0;
	StringGrid1->RowCount=2;
	StringGrid1->Rows[1]->Clear();

}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtnSaveClick(TObject *Sender)
{
	if (SaveDialog1->Execute()){
//		if (SaveDialog1->FileName)

		TFileStream *FileStream=new TFileStream(SaveDialog1->FileName, fmCreate	);
		for (int n=1; n<=Number; n++){
//			StringGrid1->Rows[n]->Text.SaveToFile(SaveDialog1->FileName);
			//StringGrid1->Rows[n]->Add(";");
			StringGrid1->Rows[n]->SaveToStream(FileStream);
			}
		FileStream->~TFileStream();
		}
}
//---------------------------------------------------------------------------

