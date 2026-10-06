# include <iostream>
using namespace std;
int sum(int n){
    int sum;
    for(int i=0;i<=n;i++) sum+=i;
    return sum;
}
int fac(int n){
    int x;
    for(int i=1;i<=n;i++) x*=i;
    return x;
}
int main(){
    int x=90;
    int y=43;
    int sum=x+y;
    cout<<sum<<endl;
    return 0;
}