#include <iostream>
#include <ctime>
using namespace std;
struct DoubleList //Тізбек бөлігінің құрылымы
{int data;            //ақпарат бөлігі
	DoubleList* next; //Келесі элементке нұсқау
	DoubleList* prev;  //Алдыңғы элементке нұсқау
};

DoubleList* head = NULL; //тізбек басы, жалпы айнымалы
//Тізбекке элемент қосу
void AddList(int value, int n)  //vale - дерек мәні, n - орны
{
	n--;
	DoubleList* node = new(DoubleList);
	node->data = value;
	node->prev = NULL;
	node->next = NULL;
	if (head == NULL)head = node; //егер тізбек бос болса
	else                         //тізбек бос болмаса
	{
		DoubleList* p = head;
		if (n==0)                          //жаңа элементті 1-ші орынға қою
		{
			node->next = head;
			head->prev = node;
			head = node;                    //тізбектің басы осы элемент
		}
		else                                //жаңа элементті 1-ші емес орынға қою
		{
			for (int i = 1; i < n && p->next != NULL; i++) p = p->next;  //n-орынға жылжу
			if (p->next != NULL) p->next->prev = node;          //егер тізбек соңы болмаса, келесінің	алдыңғысы
			node->next = p->next; //байланыстар келтіру
			p->next = node;
			node->prev = p;
			p = node;
		}
	}
}
//Тізбектен элементті өшіру
int DeleteList(int n) //n - орны
{
	int b;
	if (head == NULL) { cout << "\nTizbek bos\n\n"; return 0; }
	if (head==head->next) //егер соңғы элемент болса
	{
		b = head->data;
		delete head;        //өшіру
		head = NULL;
}
	else
	{
		DoubleList* a = head;
		for (int i = 1; i < n; i++) a = a->next;  //n - орынға жылжу
		b = a->data;
		if (a == head)head = a->next;              //егер 1-ші элемент
		else
		{
			a->next->prev = a->prev;              //тізбектен алып тастау
			a->prev->next = a->next;
		}
		delete a;
	}
	cout << n << " oryndagy " << b << " oshirildi\n";
	return 0;
}
//Тізбекті экранға шығару
void PrintList()
{
	if (head == NULL)cout << "tizbek bos\n";
	else
	{
		DoubleList* a = head;
		cout << "Tizbek elementteri: ";
		do
		{
			cout << a->data << " ";
			a = a->next;
		} while (a != NULL);
		cout << endl;
	}
}
int esep(int n)  //есепті шығару алгоритмі
{
	DoubleList* t = head;
	int i, z, min, k = 0;   //k,min - ізделінетің санның орны мен мәні
	for(i=1;i<=n;i++)         //бірінші санды іздеу
	{
		z = t->data;
		if(z>=5&&z<=15)    //бірінші санды іздеу керек
		{
			k = i;          //сан табылса, оның орны мен мәнін сақтап алу
			min = z;
			break;           //циклдан шығу
		}
		t = t->next;
	}
	if(k==0)        //ондай сан жоқ болса
	{
		cout << "sandar jok\n";
		return 0;   //функциядан шығу
	}
	if (k == n)return 0; //табылған сан соңғы болса, функциядан шығу
	t = t->next;
	for (i=k+1;i<=n;i++)  //екінші цикл, ең кішіні табу
	{
		z = t->data;
		if(z>=5 &&z<=15&&min>z) //[5,15]жататын кезекті сан белгіленгеннен кіші болса
		{
			k = i; //онда орны мен мәнін белгілеу
			min = z;
		}
		t = t->next;
	}
	if (k == n)return 0;
	DeleteList(k);  //табылған санды тұрған орнынан өшіріп
	AddList(min, n); //тізбекті соңына жазу
	return 1;
}

int main()
{
	srand(time(0));
	int i, z, n;  //n тізбектегі алғашқы элемент саны
	cout << "element sany(8-10)n=";
	cin >> n;
	for(i=1;i<=n;i++)
	{
		z = rand() % 31;  //[0,30]аралығынан кездейсоқ бүтін сан алу
		//cout<<z<<" ";
		AddList(z, i);
	}
	PrintList();
	if (esep(n))PrintList(); //егер	тізбек өзгерсе, оны жазу
	return 0;
}
