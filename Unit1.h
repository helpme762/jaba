//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *LabelMax;
	TEdit *EditMass;
	TLabel *LabelMin;
	TLabel *LabelMass;
	TStringGrid *StringGrid1;
	TBitBtn *BitBtnGo;
	TBitBtn *BitBtnClear;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TStaticText *StaticText3;
	TBitBtn *BitBtnSave;
	TSaveDialog *SaveDialog1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall EditMassKeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift);
	void __fastcall StringGrid1KeyPress(TObject *Sender, char &Key);
	void __fastcall BitBtnGoClick(TObject *Sender);
	void __fastcall BitBtnClearClick(TObject *Sender);
	void __fastcall BitBtnSaveClick(TObject *Sender);
private:	// User declarations
	int Var[128],  // основной массив масс                              
		SortNdx[128],  // отсортированный массив здесь индексы комбинаций
		MaxNdx[128],// индексы наиболее подходящей комбинации
		InterpMass, // наиболее приближенная сумма масс
		InterpNum,  // количество элементов прои этом
		NowNumber,  // кол-во элементов при текущей комбинации
		Mass,       // объем, в который все и пихается
		Number,     // количество элементов
		MaxN, MinN; // максимально и минимальное кол-во, которые можно впихнуть

	void __fastcall Select(int pos, int level);
	void __fastcall Sorten(void);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
