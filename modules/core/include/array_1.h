#ifndef ARRAY_1_H
#define ARRAY_1_H

namespace ucv
{
	template <typename T>
	class Array1
	{
	public:

		//размер массива
		typedef struct Size
		{
			int size_a;
		}Size;
		Size size;

		Array1();
		~Array1();

		//иницилизация массива
		T* init(
				int size_a
				);

		//данные массива
		T* data;

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
ucv::Array1<T>::Array1()
{
	data	=	NULL;

	size.size_a 	=	0;
}
//=======================================



//деструктор
//=======================================
template <typename T>
ucv::Array1<T>::~Array1()
{
	delete_mem();
}
//=======================================


//выделение памяти
//=======================================
template <typename T>
int ucv::Array1<T>::new_mem()
{
	 data = new T [size.size_a];

	return 0;
}
//======================================



//освобождение памяти
//=======================================
template <typename T>
int ucv::Array1<T>::delete_mem()
{
	delete [] data;
	data = NULL;
	return 0;
}
//=======================================



//инициализация
//=======================================
template <typename T>
T* ucv::Array1<T>::init(				
						int size_a
						)
{	
	if(data==NULL){
		size.size_a	=	size_a;

		new_mem();
	}else{
		delete_mem();

		size.size_a	=	size_a;
		
		new_mem();
	}

	return data;
}
//=======================================

#endif
/*End of file array_1.h*/
