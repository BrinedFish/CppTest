#include <jni.h>
#include <string>

#include<android/log.h>
#include <array>
#include <iostream>


#define TAG    "ldw-jni-test" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__) // 定义LOGD类型


#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型



/**
 *
 * 替换
 *
 * @param str
 * @param old_value
 * @param new_value
 * @return
 */
std::string&   replace_all(std::string&   str,const   std::string&   old_value,const   std::string&   new_value)
{
    while(true)   {
        std::string::size_type   pos(0);
        if(   (pos=str.find(old_value))!=std::string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}



std::string&   replace_all_distinct(std::string&   str,const   std::string&   old_value,const   std::string&   new_value)
{
    for(std::string::size_type   pos(0);   pos!=std::string::npos;   pos+=new_value.length())   {
        if(   (pos=str.find(old_value,pos))!=std::string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}


void InsertSort(int a[], int n)
{
    for(int i= 1; i<n; i++){
        if(a[i] < a[i-1]){               //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
            int j= i-1;
            int x = a[i];		 //复制为哨兵，即存储待排序元素
            a[i] = a[i-1];           //先后移一个元素
            while(x < a[j]){	 //查找在有序表的插入位置
                a[j+1] = a[j];
                j--;		 //元素后移
            }
            a[j+1] = x;		 //插入到正确位置
        }

        LOGE("########## InsertSort = %d", a[i]);			//打印每趟排序的结果
    }

}






extern "C" JNIEXPORT jstring JNICALL
Java_com_example_applicationcpp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";




    std::string haha = "可以自动提示";






    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_applicationcpp_MainActivity_stringFromHaha(JNIEnv *env, jobject instance,
                                                            jstring v_) {
    const char *v = env->GetStringUTFChars(v_, 0);


    std::string haha = "可以自动提示" ;




    std::string tt = v ;


    tt = haha + tt;


   int isEquls =  haha.compare(tt);

    env->ReleaseStringUTFChars(v_, v);





    return env->NewStringUTF(tt.c_str());
   // return env->NewStringUTF(reinterpret_cast<const char *>(isEquls));


}extern "C"
JNIEXPORT jint JNICALL
Java_com_example_applicationcpp_MainActivity_stringFromHaha2(JNIEnv *env, jobject instance,
                                                             jstring v_) {
    const char *v = env->GetStringUTFChars(v_, 0);
    //std::string haha = "可以自动提示" ;
    std::string haha = "123456" ;



    std::string haha2 = "可以自动提示" ;


    std::string tt = v ;


    tt = haha + tt;


    //返回0 相等  -1不相等
    int isEquals =  haha.compare(tt);

    LOGE("########## isEquls = %d", isEquals);


    //替换

    //std::string newHaha = replace_all(haha,"可以","真的可以");  //这种替换不了中文
    std::string newHaha = replace_all(haha,"12","21");

    std::string newHaha2 = replace_all_distinct(haha2,"可以","真的可以");

    LOGE("########## newHaha = %s", newHaha.c_str());
    LOGE("########## newHaha2 = %s", newHaha2.c_str());

    env->ReleaseStringUTFChars(v_, v);

    return  isEquals;
}




extern "C"
JNIEXPORT jint JNICALL
Java_com_example_applicationcpp_MainActivity_testArray(JNIEnv *env, jobject instance) {

    typedef std::array<int, 4> Myarray;

    Myarray c0 = { 0, 1, 2, 3 };

    // display contents " 0 1 2 3"
    for (Myarray::const_iterator it = c0.begin(); it != c0.end(); ++it){

        LOGE("########## array = %d", *it);

    }




    std::array<int, 3> a1{ { 1, 2, 3 } }; // double-braces required in C++11 (not in C++14)
    std::array<int, 3> a2 = { 1, 2, 3 };  // never required after =
    std::array<std::string, 2> a3 = { std::string("a"), "b" };

    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // ranged for loop is supported
    for (const auto& s : a3)
        std::cout << s << ' ';
    std::cout << '\n';







    std::array<int, 3> first;              // uninitialized:    {?,?,?}

    // initializer-list initializations:
    std::array<int, 3> second = { 10, 20 };   // initialized as:   {10,20,0}
    std::array<int, 3> third = { 1, 2, 3 };    // initialized as:   {1,2,3}

    // copy initialization:
    std::array<int, 3> fourth = third;     // copy:             {1,2,3}

    std::cout << "The contents of fourth are:";
    for (auto x : fourth)LOGE("########## array fourth = %d", x);



    const char* cstr = "Test string";
   // std::array<char, 12> charray;
    std::array<char, 12> charray;

    //std::memcpy(charray.data(), cstr, 12);
    std::memcpy(charray.data(), cstr, 12);
    std::cout << charray.data() << '\n';


    LOGE("########## array char = %s", charray.data());

    for(auto xx:charray)LOGE("########## array xx = %c", xx);



    return  0;

}





extern "C"
JNIEXPORT jint JNICALL
Java_com_example_applicationcpp_CppArray_testArray(JNIEnv *env, jclass type) {


    typedef std::array<int, 4> Myarray;

    Myarray c0 = { 0, 1, 2, 3 };

    // display contents " 0 1 2 3"
    for (Myarray::const_iterator it = c0.begin(); it != c0.end(); ++it){

        LOGE("########## array = %d", *it);

    }




    std::array<int, 3> a1{ { 1, 2, 3 } }; // double-braces required in C++11 (not in C++14)
    std::array<int, 3> a2 = { 1, 2, 3 };  // never required after =
    std::array<std::string, 2> a3 = { std::string("a"), "b" };

    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // ranged for loop is supported
    for (const auto& s : a3)
        std::cout << s << ' ';
    std::cout << '\n';







    std::array<int, 3> first;              // uninitialized:    {?,?,?}

    // initializer-list initializations:
    std::array<int, 3> second = { 10, 20 };   // initialized as:   {10,20,0}
    std::array<int, 3> third = { 1, 2, 3 };    // initialized as:   {1,2,3}

    // copy initialization:
    std::array<int, 3> fourth = third;     // copy:             {1,2,3}

    std::cout << "The contents of fourth are:";
    for (auto x : fourth)LOGE("########## array fourth = %d", x);



    const char* cstr = "Test string";
    // std::array<char, 12> charray;
    std::array<char, 11> charray;

    //std::memcpy(charray.data(), cstr, 12);
    std::memcpy(charray.data(), cstr, 11);
    std::cout << charray.data() << '\n';


    LOGE("########## array char = %s", charray.data());

    for(auto xx:charray)LOGE("########## array xx = %c", xx);


    int a[8] = {3,1,5,7,2,4,9,6};
    InsertSort(a,8);

    for (int i = 0; i < 8; ++i) {

        LOGE("########## a i = %d", a[i]);
    }


    return  0;

}



template <typename T>
//inline T const& Max (T const& a, T const& b)
inline const T& Max (T const& a, T const& b)  //一样的效果
{
    return a < b ? b:a;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_applicationcpp_MainActivity_testTemplate(JNIEnv *env, jobject instance) {

    LOGE("########## testTemplate = %d", 66);

    int i = 39;
    int j = 20;

    LOGE("########## Max(i, j) %d", Max(i, j));



    double f1 = 13.5;
    double f2 = 20.7;

    LOGE("########## Max(f1, f2) %f", Max(f1, f2));


   /* std::string s1 = "Hello";
    std::string s2 = "World";

    LOGE("########## Max(s1, s2) %S", Max(s1, s2));*/




    return  0;

}