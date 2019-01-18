#pragma once
struct text_position
{
	const int row, column, charSpan;

	text_position(int row, int column, int charSpan) :
		row(row), column(column), charSpan(charSpan) {}
};