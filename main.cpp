#include <iostream>
#include <fstream>
#include <vector>
#include<chrono>
#include <queue>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
ifstream f("dauteste.in");
int NumarTeste;
bool verifica(vector<int> v1, vector<int>v2)
{
    for (int i = 0; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }

    return true;
}
///Quick_Sort:
///Quick_Sort using random med of 3:
int AflarePozitie(vector<int> &arr, int start, int end);
void Quick_Sort_Med_of_3_Random(vector<int> &arr, int start, int end)
{
    if(start<end)
    {
        int poz = AflarePozitie(arr, start, end);
        Quick_Sort_Med_of_3_Random(arr, start, poz-1);
        Quick_Sort_Med_of_3_Random(arr, poz+1, end);

    }
}
int AflarePozitie(vector<int> &arr, int start, int end)
{
    int RandomIndex1, RandomIndex2, RandomIndex3, pivot, i, pozitie_pivot, j;

    RandomIndex1 = rand()%(end-start) + start;

    RandomIndex2 = rand()%(end-start) + start;

    RandomIndex3 = rand()%(end-start) + start;

    if(arr[RandomIndex1] > arr[RandomIndex2])
    {
        if(arr[RandomIndex2] > arr[RandomIndex3])
        {
            pivot = arr[RandomIndex2], pozitie_pivot = RandomIndex2;
        }
        else if(arr[RandomIndex1] > arr[RandomIndex3])
        {
            pivot = arr[RandomIndex3], pozitie_pivot = RandomIndex3;
        }
        else
        {
            pivot = arr[RandomIndex1], pozitie_pivot = RandomIndex1;
        }
    }
    else
    {
        if(arr[RandomIndex1] > arr[RandomIndex3])
        {
            pivot = arr[RandomIndex1], pozitie_pivot = RandomIndex1;
        }
        else if(arr[RandomIndex2] > arr[RandomIndex3])
        {
            pivot = arr[RandomIndex3], pozitie_pivot = RandomIndex3;
        }
        else
        {
            pivot = arr[RandomIndex2], pozitie_pivot = RandomIndex2;
        }
    }

    swap(arr[end], arr[pozitie_pivot]);

    pivot = arr[end];
    int pIndex = start;
    for(i = start; i < end; i++)
    {

        if(arr[i] <= pivot)
        {

            int aux = arr[i];
            arr[i] = arr[pIndex];
            arr[pIndex] = aux;
            pIndex++;
        }
    }

    int aux = arr[end];
    arr[end] = arr[pIndex];
    arr[pIndex] = aux;
    return pIndex;
}
///QuickSort cu mediana din primul element, elementul din mijloc si ultimul element:
int Aflare_Pozitie(vector<int>&arr, int left, int right);
void Quick_Sort_Med_of_3(vector<int> &arr, int left, int right)
{
    if(left<right)
    {
        int poz = Aflare_Pozitie(arr, left, right);
        Quick_Sort_Med_of_3(arr, left, poz-1);
        Quick_Sort_Med_of_3(arr, poz+1, right);

    }
}
int Aflare_Pozitie(vector<int>&arr, int left, int right)
{
    ///Getting median of 3 by sorting first, middle and last;
    int mid = left+ (right-left)/2;
    if(arr[left] > arr[mid])
        swap(arr[left], arr[mid]);
    if(arr[mid]>arr[right])
        swap(arr[mid], arr[right]);
    if(arr[left]>arr[mid])
        swap(arr[left], arr[mid]);

    swap(arr[mid], arr[right-1]);
    int pivot = arr[right-1];
    int i = left;
    int pIndex = left;
    for(i = left; i<right-1; i++)
    {
        if(arr[i] <= pivot)
        {
            swap(arr[i], arr[pIndex]);
            pIndex++;
        }
    }
    swap(arr[right-1], arr[pIndex]);
    return pIndex;
}

///RadixSort Algorithm:
int GetMax(vector<int>arr, int size)
{
    int i, maxx = arr[0];
    for(i = 1; i < size; ++i)
        if(arr[i] > maxx)
            maxx = arr[i];
    return maxx;
}

///Radix_Sort using buckets
///fara shift
void Radix_Sort_Using_Bucket_fara_shift(vector<int>&arr, int n, int baza)
{
    vector<queue<int>>queues(baza);
    int maxim = GetMax(arr, n);
    long long cifra = 1;
    while(maxim/cifra>0)
    {
        for(int i = 0; i< arr.size(); ++i)
        {
            queues[(arr[i]/cifra)%baza].push(arr[i]);
        }
        int contor = 0;
        for(int i = 1; i <= baza; ++i)
        {
            //for(long long j = 0; j<queues[i].size(); j++)
            while(!queues[i-1].empty())
            {
                arr[contor++] = queues[i-1].front();
                queues[i-1].pop();
            }
            ;
        }

        cifra *= baza;
    }
}

void Radix_Sort_using_bucket_cu_shift(vector<int>&arr, int n, int baza)
{
    vector<queue<int>>queues(1<<baza);
    int maxim = GetMax(arr, n);
    int cont = 0;
    //long long cifra = 1;
    while((maxim>>(cont*baza))>0)
    {
        for(int i = 0; i< arr.size(); ++i)
        {
            queues[(arr[i]>>(cont*baza))%(1<<baza)].push(arr[i]);
        }
        int contor = 0;
        for(int i = 1; i <= (1<<baza); ++i)
        {

            while(!queues[i-1].empty())
            {
                arr[contor++] = queues[i-1].front();
                queues[i-1].pop();
            }
        }
        ++cont;
    }
}
///Radix_Sort using Count:
void CountingSort(vector<int>& arr, int size, long long cifra, int baza);
void Radix_Sort_using_count(vector<int>& arr, int size, int baza)
{
    int maxim = GetMax(arr, size);
    long long cifra = 1;
    while(maxim/cifra > 0)
    {
        CountingSort(arr, size, cifra, baza);
        cifra *= baza;
    }
}

void CountingSort(vector<int>& arr, int size, long long cifra, int baza)
{
    vector<int>output(size);
    int contor[baza] = {0};
    for(long long i = 0; i < size; ++i)
        contor[(arr[i]/cifra)%baza]++;
    for(int i = 1; i < baza; ++i)
        contor[i] += contor[i-1];
    for(int i = size - 1; i >= 0; --i)
    {
        output[contor[(arr[i]/cifra)%baza]-1] = arr[i];
        contor[(arr[i]/cifra)%baza]--;
    }
    for(int i = 0; i < size; ++i)
        arr[i] = output[i];

}
///MergeSort Algorithm:
void MergeSort(vector<int>& arr, int start, int end)
{
    if(start<end)
    {
        int mid = start+ (end-start)/2;
        MergeSort(arr, start, mid);
        MergeSort(arr, mid+1, end);

        int i, j, p = 0;
        vector<int>arrayaux(end-start+1);
        i = start, j = mid+1;

        while(i <= mid && j <= end)
        {
            if(arr[i] < arr[j])
            {
                arrayaux[p] = arr[i];
                i++, p++;
            }
            else
            {
                arrayaux[p] = arr[j];
                j++;
                p++;
            }

        }
        while(i <= mid)
        {
            arrayaux[p] = arr[i];
            i++;
            p++;
        }
        while(j <= end)
        {
            arrayaux[p] = arr[j];
            j++;
            p++;
        }
        p = 0;
        for(int i = start; i <= end; i++)
        {
            arr[i] = arrayaux[p], p++;
        }
    }
}

///Shell_Sort Algorithm with gap = n/2:
void ShellSort_first_gap(vector<int>&v, int size)
{
    int i, temp, j, gap;
    for(gap = size>>1; gap > 0; gap >>=1)
    {
        for(j = gap; j<size; j+=1)
        {
            temp = v[j];
            for(i = j; i >= gap && v[i-gap] > temp; i-= gap)
            {
                v[i] = v[i-gap];

            }
            v[i] = temp;
        }
    }
}
///Shell_Sort with gap = 2^k+1;
int find_gap(int n)
{
    int putere_doi = 1;
    while(putere_doi<<1 <n)
        putere_doi <<= 1;
    putere_doi-=1;
    return putere_doi;
}
void Shell_Sort_second_gap(vector<int>&v, int size)
{
    int i, temp, j, gap, putere;
    //for(gap = putere; gap > 0; gap>>1)
    gap = find_gap(size);
    while(gap>0)
    {
        for(j = gap; j<size; j+=1)
        {
            temp = v[j];
            for(i = j; i >= gap && v[i-gap] > temp; i-= gap)
            {
                v[i] = v[i-gap];

            }
            v[i] = temp;
        }
        gap >>= 1;
    }
}

///Insertion sort:
void Insertion_Sort(vector<int>&v, int n)
{
    int i, j, num;
    for(i = 1; i< n; ++i)
    {
        j = i - 1;
        num = v[i];
        while(num<v[j] && j >= 0)
        {
            v[j+1] = v[j];
            j -= 1;
        }
        v[j+1] = num;
    }
}

int NumarulDeNumere, NumarMaximPosibil, NrRandom;
int main()
{
    srand(time(NULL));
    f>>NumarTeste;
    int j, b, B;
    for(int k = 1; k <= NumarTeste; k++)
    {   cout<<"Testul numarul: "<<k<<'\n';

        long long ElementulMaximDinVector = 0;

            f>>NumarulDeNumere>>NumarMaximPosibil;
            if(NumarulDeNumere <= 1000000)
                b = 8, B =256 ;
            else
            {
                b = 15, B = 65536;
            }
            cout<<"Numarul de elemente de sortat: "<<NumarulDeNumere<<'\n'<<"Numarul maxim posibil: "<<NumarMaximPosibil<<'\n';
            vector<int> vect(NumarulDeNumere), v(NumarulDeNumere), vector_aux(NumarulDeNumere);
            if(k <= 4)
            {///Teste cu numere random
              for(j = 0; j < NumarulDeNumere; ++j)
              {
                NrRandom = rand() % NumarMaximPosibil;
                vect[j] = NrRandom;
                v[j] = NrRandom;
                vector_aux[j] = NrRandom;
                if(vect[j]>ElementulMaximDinVector)
                    ElementulMaximDinVector = vect[j];
              }
            }
            else if(k == 5)
            {
                ///Test 50% sortat si 50% random:
                ElementulMaximDinVector = NumarulDeNumere/2 - 1;
                for(j = 0; j < NumarulDeNumere/2; ++j)
                {
                     vect[j] = j;
                     v[j] = j;
                     vector_aux[j] = j;
                }
                for(j = NumarulDeNumere/2; j < NumarulDeNumere; ++j)
                {
                    NrRandom = rand() % NumarMaximPosibil;
                    vect[j] = NrRandom;
                    v[j] = NrRandom;
                    vector_aux[j] = NrRandom;
                    if(vect[j]>ElementulMaximDinVector)
                    ElementulMaximDinVector = vect[j];
                }

            }
            else if(k <= 7)
            { ///Teste cu numere sortate
                ElementulMaximDinVector = NumarulDeNumere - 1;
                for(j = 0; j < NumarulDeNumere; ++j)
                {
                     vect[j] = j;
                     v[j] = j;
                     vector_aux[j] = j;
                }
            }
            else if(k <= 9)
            { ///Teste cu numere reverse sorted
                ElementulMaximDinVector = NumarulDeNumere-1;
                for(j = NumarulDeNumere-1; j >= 0; j--)
                {
                     vect[NumarulDeNumere-j-1] = j;
                     v[NumarulDeNumere-j-1] = j;
                     vector_aux[NumarulDeNumere-j-1] = j;
                     //if(vect[j]>ElementulMaximDinVector)
                     //ElementulMaximDinVector = vect[j];
                }
            }
            else
            { ///Test cu toate elementele egale:
              NrRandom = rand() % NumarMaximPosibil;
              ElementulMaximDinVector = NrRandom;
              for(j = 0; j < NumarulDeNumere; ++j)
                {
                     vect[j] = v[j] = vector_aux[j] = NrRandom;
                     //v[j] = j;
                     //vector_aux[j] = j;
                     //if(vect[j]>ElementulMaximDinVector)
                     //ElementulMaximDinVector = vect[j];
                }
            }
        sort(vector_aux.begin(), vector_aux.end());
        cout<<endl<<"Numarul maxim din vector este: "<<ElementulMaximDinVector<<'\n';

        ///Prima sortare - ShellSort:
        if(NumarulDeNumere <= 100000)
        {cout<<"Sortare ShellSort unde gap = n/2: \n";
        auto start = chrono::steady_clock::now();
        ShellSort_first_gap(v, v.size());
        auto end = chrono::steady_clock::now();
        double elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde"<<"\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        cout<<"Sortare ShellSort unde gap = 2^k-1: \n";
        start = chrono::steady_clock::now();
        Shell_Sort_second_gap(v, v.size());
        end = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde"<<"\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
         {
            v[m] = vect[m];
         }
        }
        ///A doua sortare - MergeSort:
        cout<<endl<<"Sortare MergeSort: ";
        auto start = chrono::steady_clock::now();
        MergeSort(v, 0, v.size()-1);
        auto end = chrono::steady_clock:: now();
        double elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        ///A treia sortare - RadixSort:

        cout<<endl<<"Sortare RadixSort in baza 2: ";
        start = chrono::steady_clock::now();
        Radix_Sort_using_bucket_cu_shift(v, v.size(), 2);
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        cout<<endl<<"Sortare RadixSort in baza 2^8: ";
        start = chrono::steady_clock::now();
        Radix_Sort_using_bucket_cu_shift(v, v.size(), 6);
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        cout<<endl<<"Sortare RadixSort folosind Buckets fara shiftari in baza 2^16: ";
        start = chrono::steady_clock::now();
        Radix_Sort_Using_Bucket_fara_shift(v, v.size(), B);
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        cout<<endl<<"Sortare RadixSort folosind Buckets cu shiftari: ";
        start = chrono::steady_clock::now();
        Radix_Sort_using_bucket_cu_shift(v, v.size(), b);
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        cout<<endl<<"Sortare RadixSort folosind CountSort in baza 2^16: ";
        start = chrono::steady_clock::now();
        Radix_Sort_using_count(v, v.size(), B);
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        ///A patra sortare - QuickSort:
        cout<<endl<<"Sortare QuickSort folosind mediana din 3 random: ";
        start = chrono::steady_clock::now();
        Quick_Sort_Med_of_3_Random(v, 0, v.size()-1);
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }


        cout<<endl<<"Sortare QuickSort folosind mediana din 3: ";
        start = chrono::steady_clock::now();
        Quick_Sort_Med_of_3(v, 0, v.size()-1);
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        ///STL-sort:
        cout<<endl<<"STL-Sort: ";
        start = chrono::steady_clock::now();
        sort(v.begin(), v.end());
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
        for(int m = 0; m<v.size(); ++m)
        {
            v[m] = vect[m];
        }

        ///Insertion_Sort:
       if(NumarulDeNumere <= 100000)
       {
        cout<<endl<<"Insertion_Sort: ";
        start = chrono::steady_clock::now();
        Insertion_Sort(v, v.size());
        end = chrono::steady_clock:: now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count());
        cout<<"\n"<<"Durata sortarii a fost de: "<<elapsed_time/1e9<<" secunde\n\n";
        if(verifica(v, vector_aux))
            cout<<"Vectorul a fost sortat corect!\n";
        else
            cout<<"Vectorul nu a fost sortat corect!\n";
       }


    }
    return 0;
}
