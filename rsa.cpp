/*
 * rsa.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: Viet
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <string.h>
//#include <stdlib.h>

using namespace std;

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

int prime(long int);
void cal_e();
long int cal_d(long int);
void encrypt();
void decrypt();

int main()
{
	cout << "Enter first prime number: ";
	cin >> p;
	flag = prime(p);
	if(flag==0)
	{
		cout << "\nNumber inputed that is not a prime number!!!";
		exit(1);
	}

	cout << "Enter second prime number: ";
	cin >> q;
	flag = prime(q);
	if ((flag==0) || (p==q))
	{
		cout << "\nNumber inputed that is not a prime number!!!";
		exit(1);
	}

   	cout << "Input a string: ";
    fflush(stdin);
   	cin.getline(msg,sizeof(msg));
   	cout << "\nString inputed from console is: " << msg << endl;

    for (i=0; msg[i] != 0; i++)
    {
        m[i] = msg[i];
    }

   	//Calculation
    n=p*q;
    t=(p-1)*(q-1);
    cal_e();

    //This generate Public and Private keys
    for (i = 0; i < j - 1; i++)
    {
        cout << " Public key (n,e) is: (" << n << "," << e[i] << ")" << endl;
        cout << "Private key (n,d) is: (" << n << "," << d[i] << ")" << endl;
    }

    encrypt();
    decrypt();
   	return 0;
}

int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

void cal_e()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if((t%i) == 0)
        {
            continue;
        }
        flag = prime(i);
        if((flag==1) && (i!=p) && (i!=q))
        {
            e[k] = i;
            flag = cal_d(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if(k==99)	//???????????????? 99
            {
                break;
            }
        }
    }
}

long int cal_d(long int x)
{
    long int k=1;
    while (1)
    {
    	k=k+t;
        if((k%x)==0)
        {
            return(k/x);
        }
    }
}

void encrypt()
{
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while (i!=len)
    {
        pt = m[i];
        pt = pt - 96;	//???????????????? 96
        k = 1;
        for (j = 0; j < key; j++)
        {
            k=k*pt;
            k=k%n;
        }
        temp[i]=k;
        ct=k+96;	//???????????????? 96
        en[i]=ct;
        i++;
    }
    en[i] = -1;
    cout << "\nMessage have been encrypted to: ";
    for(i=0; en[i]!=-1; i++)
    {
        printf("%c",en[i]);
    }
}//End encrypt()

void decrypt()
{
	long int pt, ct, key = d[0], k;
    i = 0;
    while(en[i]!=-1)
    {
        ct = temp[i];
        k = 1;
        for(j = 0; j<key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;	//???????????????? 96
        m[i] = pt;
        i++;
    }

    m[i] = -1;
    cout << "\nMessage have been decrypted to: ";
    for(i = 0; m[i]!=-1; i++)
    {
        printf("%c", m[i]);
    }

}

