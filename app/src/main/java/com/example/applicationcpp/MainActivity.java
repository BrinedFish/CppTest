package com.example.applicationcpp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        final TextView tv = findViewById(R.id.sample_text);


        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                tv.setText(stringFromJNI());
                tv.setText(stringFromHaha("haha"));
                tv.setText(String.valueOf(stringFromHaha2("haha")));
                testArray();

                testTemplate();


                CppArray.testArray();
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String stringFromHaha(String v);
    public native int stringFromHaha2(String v);
    public native int testArray();
    public native int testTemplate ();
}
