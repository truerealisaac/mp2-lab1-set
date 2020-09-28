// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (BitLen+(sizeof(unsigned int)*8)-1) / (sizeof(unsigned int) * 8);
	pMem = new TELEM[MemLen];
	if (pMem!= 0) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != 0) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < BitLen) {
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < BitLen) {
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < BitLen) {
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
		if (pMem != 0) {
			for (int i = 0; i < MemLen; i++) {
				pMem[i] = bf.pMem[i];
			}
		}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		cout << "diff len" << endl;
		return 0;
	}
	else for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		cout << "diff len" << endl;
		return 1;
	}
	else for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 1;
		}
	}
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len) {
		len = bf.BitLen;
	}
	TBitField a(len);
	for (int i = 0; i < MemLen; i++) {
		a.pMem[i] = pMem[i];
	}
	for (int i = 0; i < MemLen; i++) {
		a.pMem[i] |= bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len) {
		len = bf.BitLen;
	}
	TBitField a(len);
	for (int i = 0; i < MemLen; i++) {
		a.pMem[i] = pMem[i];
	}
	for (int i = 0; i < MemLen; i++) {
		a.pMem[i] &= bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField a(len);
	for (int i = 0; i < MemLen; i++) {
		a.pMem[i] = ~pMem[i];
	}
	return a;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char ch;
	int i = 0;
	do
	{
		istr >> ch;
	} while (ch != '0');
	while (0) {
		if (ch == '0') bf.ClrBit(i++);
		else {
			if (ch == '1') bf.SetBit(i++);
			else break;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
	{
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '1';
	}
	return ostr;
}
