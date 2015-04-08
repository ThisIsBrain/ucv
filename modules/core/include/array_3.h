#ifndef ARRAY_3_H
#define ARRAY_3_H


namespace ucv
{
	template <typename T>
	class Array3
	{
	public:

		//размер массива
		typedef struct Size
		{
			int size_a;
			int size_b;
			int size_c;
		}Size;
		Size size;

		Array3();
		~Array3();

		//иницилизация массива
		T*** init(
				int size_a,
				int size_b,
				int size_c
				);

		//данные массива
		T*** data;

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
ucv::Array3<T>::Array3()
{
	data	=	NULL;

	size.size_a 	=	0;
	size.size_b		=	0;
	size.size_c		=	0;
}
//=======================================



//деструктор
//=======================================
template <typename T>
ucv::Array3<T>::~Array3()
{
	delete_mem();
}
//=======================================


//выделение памяти
//=======================================
template <typename T>
int ucv::Array3<T>::new_mem()
{
	 data = new T** [size.size_a];

	 for(int b=0; b<size.size_a; b++){
	 	data[b] = new T* [size.size_b];

	 	for(int c=0; c<size.size_b; c++){
	 		data[b][c] = new T [size.size_c];
	 	}
	 }

	return 0;
}
//======================================



//освобождение памяти
//=======================================
template <typename T>
int ucv::Array3<T>::delete_mem()
{
	for(int b=0; b<size.size_b; b++){
		for(int c=0; c<size.size_c; c++){
			delete [] data[b][c];
		}
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
T*** ucv::Array3<T>::init(				
						int size_a,
						int size_b,
						int size_c
						)
{	
	if(data==NULL){
		size.size_a	=	size_a;
		size.size_b	=	size_b;
		size.size_c	=	size_c;

		new_mem();
	}else{
		delete_mem();

		size.size_a	=	size_a;
		size.size_b	=	size_b;
		size.size_c	=	size_c;
		
		new_mem();
	}

	return data;
}
//=======================================



#endif
/*End of file array_2.h*/
