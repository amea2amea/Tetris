#ifndef Array2D_h
#define Array2D_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include <vector>

/*--------------------------*/
/*	テンプレートクラス		*/
/*--------------------------*/
template <typename TYPE>

class Array2D															/* 1次元配列を2次元のように操作するためのクラス		*/
{
/*--------------*/
/*	メンバ変数	*/
/*--------------*/
private:
	std::vector<TYPE>	m_Array2D;
	int					m_Size_X;
	int					m_Size_Y;

/*--------------*/
/*	メンバ関数	*/
/*--------------*/
public:
	void operator=(const Array2D& other) {};							/* クラスの代入操作( = 操作)は禁止					*/
	Array2D();															/* コンストラクタ									*/
	Array2D( unsigned int, unsigned int );								/* コンストラクタ									*/
	Array2D( const Array2D& );											/* コピーコンストラクタ								*/
	~Array2D();															/* デストラクタ										*/
	void		Clear();												/* メモリの消去										*/
	void		SetSize( unsigned int, unsigned int );					/* 配列の作成										*/
	const TYPE&	operator()( unsigned int, unsigned int ) const;			/* 2次元配列操作の参照								*/
	TYPE&		operator()( unsigned int, unsigned int );				/* 2次元配列操作の設定								*/

};

#endif