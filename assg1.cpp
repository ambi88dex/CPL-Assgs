#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int cmpr(vector<int>& a, vector<int>& b)
{
    int len1=a.size();
    int len2=b.size();
    int i,j;
    ll diff,n;
    ll first_is_bigger=0;
    ll eq=0;
    ll borrow=0;
    if(len1>len2)
    {
        first_is_bigger=1;
    }
    else if(len1 < len2)
    {
        first_is_bigger=0;
    }
    else
    {
        i=0;
        while( i<len1 && a[i]==b[i])
        {
            i++;
        }
        if(i==len1)
        {
            eq=1;
        }
        else
        {
            if(a[i]>b[i])
            {
                first_is_bigger=1;
            }
            else
            {
                first_is_bigger=0;
            }
        }

    }
    if(eq==1)
    {
        return 0;
    }
    else if(first_is_bigger==1)
    {
        return 1;
    }
    else
    {
        return -1;
    }

}
vector<int> add( vector<int>& a, vector<int>& b)
{
    ll i,len1,len2;
    len1=a.size();
    len2=b.size();
    ll carry=0;
    vector<int>ret;
    for(i=0;i<min(len1,len2);i++)
    {

        ret.push_back((a[len1-1-i]+b[len2-1-i]+carry)%10);
         carry=(a[len1-1-i]+b[len2-1-i]+carry)/10;
    }
    if(len1>len2)
    {
        for(;i<len1;i++)
        {
            ret.push_back((a[len1-i-1]+carry)%10);
            carry=(a[len1-1-i]+carry)/10;
        }
    }
    else
    {
        for(;i<len2;i++)
        {
            ret.push_back((b[len2-i-1]+carry)%10);
            carry=(b[len2-i-1]+carry)/10;
        }
    }
    if(carry!=0)
    {
        ret.push_back(carry);
    }
    reverse(ret.begin(),ret.end());
    return ret;
}
vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int>ret;
     ll  borrow=0;
     ll i,diff;
     ll len1=a.size();
     ll len2 = b.size();
            for(i=0;i<len2;i++)
            {
                diff=a[len1-1-i]-b[len2-i-1]-borrow;
                if(diff<0)
                {
                    borrow=1;
                    diff+=10;
                }
                else
                {
                    borrow=0;
                }
                ret.push_back(diff);
            }
            while(i<len1)
            {
                diff=a[len1-i-1]-borrow;
                    if(diff<0)
                    {
                        borrow=1;
                        diff+=10;
                    }
                    else
                    {
                        borrow=0;
                    }
                ret.push_back(diff);
                i++;
            }
    reverse(ret.begin(),ret.end());
    return ret;
}

vector<int>prod(vector<int>a,vector<int>b)
{
    vector<int>ret;
    ll i,j;
    ll len1,len2;
    len1=a.size();
    len2=b.size();
    ll carry=0;
    ll val;
    for(i=0;i<len2;i++)
    {
        carry=0;
        for(j=0;j<len1;j++)
        {
            if(i==0)
            {
                val=(a[len1-j-1]*b[len2-i-1])+carry;
                carry=val/10;
                val%=10;
                ret.push_back(val);
            }
            else
            {
                val=(a[len1-j-1]*b[len2-i-1])+carry;
                if(i+j<ret.size())
                {
                    ret[i+j]+=val;
                    carry=ret[i+j]/10;
                    ret[i+j]%=10;
                }
                else
                {
                    carry=val/10;
                    val=val%10;
                    ret.push_back(val);
                }
            }
        }
        while(carry!=0)
        {
            if(i+j<ret.size())
            {
                ret[i+j]+=carry;
                carry=ret[i+j]/10;
                ret[i+j]%=10;
            }
            else
            {
                ret.push_back(carry%10);
                carry/=10;
            }
            j++;
        }

    }
    reverse(ret.begin(),ret.end());
    return ret;
}
int main()
{
    ll x;
    for(x=0;x<75;x++)
    {
        cout<<"-";
    }
    for(x=0;x<30;x++)
    {
        cout<<" ";
    }
    cout<<"CPL Assignment #1"<<endl;
    for(x=0;x<24;x++)
    {
        cout<<" ";
    }
    cout<<" Name:- Anish Kelkar "<<endl;
    for(x=0;x<24;x++)
    {
        cout<<" ";
    }
    cout<<" Roll no:- BT15CSE040 "<<endl;
    for(x=0;x<75;x++)
    {
        cout<<"-";
    }
    cout<<endl;
    string astr;
    string bstr;
    int t;
    cout<<"Enter number of testcases to be tested"<<endl;
    cin>>t;
    cout<<"The format of input is :-\nInput the number along with the sign\nExample :- give input as -123 and not - 123\n"<<endl;
    cout<<endl;
    while(t--)
    {
     //cout<<"Input the number along with the sign\nExample :- give input as -123 and not - 123"<<endl;
    cin>>astr;
    //cout<<"Input the number along with the sign\nExample :- give input as -123 and not - 123"<<endl;
    cin>>bstr;
    ll len1=astr.size();
    ll len2=bstr.size();
    //int *a=(int*)malloc(len1*sizeof(int));
    //int *b=(int*)malloc(len2*sizeof(int));
    vector<int>a;
    vector<int>b;
    vector<int>sum;
    vector<int>diff;
    vector<int>mult;
    vector<int>div;
    ll i,j;
        int sign1,sign2;
        /*cout<<"For entering a non-negative number press 1 else press 0"<<endl;
        cin>>sign1;
        cout<<"Enter the first BigInteger"<<endl;*/
        i=0;
        if(astr[0]=='-')
        {
            sign1=0;
            i++;
        }
        else
        {
            sign1=1;
        }
                for(;i<astr.size();i++)
                {
                    a.push_back((int)astr[i]-48);
                }
                /*
                cout<<"For entering a non-negative number press 1 else press 0"<<endl;
                cout<<"Enter the second BigInteger"<<endl;
                cin>>sign2;*/
                int signs,signd,signm;
                i=0;
                if(bstr[0]=='-')
                {
                    sign2=0;
                    i++;
                }
                else
                {
                    sign2=1;
                }
                for(;i<bstr.size();i++)
                {
                    b.push_back((int)bstr[i]-48);
                }
                if(sign1==1 && sign2==1)
                {
                    int sign=cmpr(a,b);
                //cout<<sign<<endl;
                    signm=1;
                    signs=1;
                    if(sign<0)
                    {
                        sum=add(a,b);
                        diff=sub(b,a);
                        signd=0;
                        mult=prod(b,a);

                    }
                    else
                    {
                        sum=add(a,b);
                        signd=1;
                        diff=sub(a,b);
                        mult=prod(a,b);
                    }
                }
            else if(sign1==0 && sign2==1)
            {
                int sign=cmpr(a,b);
                //cout<<sign<<endl;
                    signm=0;
                    //signs=1;
                    signd=0;
                    if(sign<0)
                    {
                        sum=sub(b,a);
                        signs=1;
                        diff=add(a,b);
                        mult=prod(b,a);

                    }
                    else
                    {
                        sum=sub(a,b);
                        signs=0;
                        diff=add(a,b);
                        mult=prod(a,b);
                    }
            }
            else if(sign1==1 && sign2==0)
            {
                   int sign=cmpr(a,b);
                //cout<<sign<<endl;
                    signm=0;
                    signd=1;
                    if(sign<0)
                    {
                        sum=sub(b,a);
                        signs=0;
                        diff=add(b,a);
                        mult=prod(b,a);

                    }
                    else
                    {
                        sum=sub(a,b);
                        signs=1;
                        diff=add(a,b);
                        mult=prod(a,b);
                    }
            }
            else
            {
                int sign=cmpr(a,b);
                //cout<<sign<<endl;
                    signm=1;
                    signs=0;
                    if(sign<0)
                    {
                        sum=add(a,b);
                        signd=1;
                        diff=sub(b,a);
                        mult=prod(b,a);

                    }
                    else
                    {
                        sum=add(a,b);
                        signd=0;
                        diff=sub(a,b);
                        mult=prod(a,b);
                    }
            }
                    cout<<"The Sum of the numbers is :";
                    if(signs==0)
                    {
                        cout<<"-";
                    }
                    for(i=0;i<sum.size();i++)
                    {
                        cout<<sum[i];

                    }
                    cout<<endl;
                    cout<<"The Difference of the numbers is :";
                    if(signd==0)
                    {
                        cout<<"-";
                    }
                    for(i=0;i<diff.size();i++)
                    {
                        cout<<diff[i];

                    }
                    cout<<endl;
                    cout<<"The Product of the numbers is :";
                    if(signm==0)
                    {
                        cout<<"-";
                    }
                    mult=prod(a,b);
                    for(i=0;i<mult.size();i++)
                    {
                        cout<<mult[i];
                    }
                    cout<<endl;
                    cout<<endl;
    }
    return 0;
}
