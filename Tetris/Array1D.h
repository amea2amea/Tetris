#ifndef Array1D_h
#define Array1D_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include <vector>

/*--------------------------*/
/*	テンプレートクラス		*/
/*--------------------------*/
template <typename TYPE>															

class Array1D														/* 1次元配列を操作するためのクラス		*/
{
/*--------------*/
/*	メンバ変数	*/
/*--------------*/
private:
	std::vector<TYPE>		m_Array1D;								/* 配列データ							*/
	int						m_Size;									/* 配列サイズ							*/
	int						m_StartPoint;							/* 配列開始位置							*/

/*--------------*/
/*	メンバ関数	*/
/*--------------*/	
public:
	void operator=(const Array1D& other) {};						/* クラスの代入操作( = 操作)は禁止		*/
	Array1D();														/* コンストラクタ						*/
	Array1D( unsigned int, int);									/* コンストラクタ						*/
	Array1D( const Array1D& );										/* コピーコンストラクタ					*/
	~Array1D();														/* デストラクタ							*/
	void		Clear();											/* メモリの消去							*/
	void		SetSize( unsigned int, int );						/* 配列の作成							*/
	const TYPE&	operator()( int ) const;							/* ()による指定された配列位置への参照	*/
	TYPE&		operator()( int );									/* ()による指定された配列位置への設定	*/
	const TYPE&	operator[]( int ) const;							/* []による指定された配列位置への参照	*/
	TYPE&		operator[]( int );									/* []による指定された配列位置への設定	*/

};

#endif
