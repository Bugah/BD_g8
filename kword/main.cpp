/* ----------------------------------------------------------------------------
 * Title: Text.h --------------------------------------------------------------
 * Author: andre --------------------------------------------------------------
 * Created on: Oct 23, 2012 ---------------------------------------------------
 * Last Changed on: Oct 25, 2012 ----------------------------------------------
 * ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */

#include "Text.h"

int main(void) {
	Text text1, text2, text3, text4, text5;

	text1 = "Temos que testar mais um dos metodos";
	cout << text1.getTxt() << endl;

	text2 = text1.copy(0, 3);
	cout << "Text between 0 and 3 (text1):" << endl;
	cout << text2.getTxt() << endl;
	cout << "Finish!" << endl << endl;

	text3 = text1.until("dos");
	cout << "Text until the 'dos' word (text1) " << endl;
	cout << text3.getTxt() << endl;
	cout << "Finish!" << endl << endl;

	text4 = text1.allWith('e');
	cout << "Words with 'e' (text1) " << endl;
	cout << text4.getTxt() << endl;
	cout << "Finish!" << endl << endl;

	text5 = text1.exceptWith('e');
	cout << "Words without 'e' (text1) " << endl;
	cout << text5.getTxt() << endl;
	cout << "Finish!" << endl << endl;

	return 0;
}
