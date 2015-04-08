#ifndef ARRAY_2_H
#define ARRAY_2_H

namespace ucv
{
	template <typename T>
	class Array2
	{
	public:

		//размер массива
		typedef struct Size
		{
			int size_a;
			int size_b;
		}Size;
		Size size;

		Array2();
		~Array2();

		//иницилизация массива
		T** init(
				int size_a,
				int size_b
				);

		//данные массива
		T** data;

	private:

		//выделение памяти
		int new_mem();

		//освобождение памяти
		int delete_mem();
	};
}


//конструктор
//=======================================
template <typename T>
ucv::Array2<T>::Array2()
{
	data	=	NULL;

	size.size_a 	=	0;
	size.size_b		=	0;
}
//=======================================



//деструктор
//=======================================
template <typename T>
ucv::Array2<T>::~Array2()
{
	delete_mem();
}
//=======================================


//выделение памяти
//=======================================
template <typename T>
int ucv::Array2<T>::new_mem()
{
	 data = new T* [size.size_a];

	 for(int b=0; b<size.size_a; b++){
	 	data[b] = new T [size.size_b];
	 }

	return 0;
}
//======================================



//освобождение памяти
//=======================================
template <typename T>
int ucv::Array2<T>::delete_mem()
{
	for(int b=0; b<size.size_b; b++){
		delete [] data[b];
	}

	delete [] data;
	data = NULL;
	return 0;
}
//=======================================



//инициализация
//=======================================
template <typename T>
T** ucv::Array2<T>::init(				
						int size_a,
						int size_b
						)
{	
	if(data==NULL){
		size.size_a	=	size_a;
		size.size_b	=	size_b;

		new_mem();
	}else{
		delete_mem();

		size.size_a	=	size_a;
		size.size_b	=	size_b;
		
		new_mem();
	}

	return data;
}
//=======================================

#endif
/*End of file array_2.h*/
