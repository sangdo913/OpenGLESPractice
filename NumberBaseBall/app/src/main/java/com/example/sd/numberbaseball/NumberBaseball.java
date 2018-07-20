package com.example.sd.numberbaseball;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Button;
import android.widget.*;

public class NumberBaseball extends AppCompatActivity {
    private Button enterButton, clearButton;
    private TextView sizeView, mView, yView,  typeView;
    private EditText stringText;

    public int turn;
    public String myNum;
    public int sz;

    public class clearListener implements Button.OnClickListener{
        @Override
        public void onClick(View v){
            turn = 1;
            myNum  = stringText.getText().toString();
            if(myNum.length() != 4){
                typeView.setText("invalid!");
                return;
            }
            clear(myNum);

            sz = size();
            sizeView.setText(Integer.toString(sz));

            String nextNum = whatNext();
            yView.setText(nextNum);
            mView.setText("");
            typeView.setText("type opponent nums said");
        }
    }
    public class enterListener implements Button.OnClickListener{
        @Override
        public void onClick(View v){
            String str, res, log;

            switch(turn){
                case 0:
                     str = stringText.getText().toString();

                    if(str.length() != 6) {
                        typeView.setText("invalid!");
                        break;
                    }

                    res = yourQuery(str);

                    log = yView.getText().toString();
                    log += " " + res + "\n";
                    log += whatNext();
                    int sz = size();

                    sizeView.setText(sz == 1 ? "Last!!!" : Integer.toString(sz));

                    yView.setText(log);

                    turn = 1;
                    typeView.setText("type nums opponent said");

                    break;
                case 1:
                    str = stringText.getText().toString();

                    if(str.length() != 4) {
                        typeView.setText("invalid!");
                        break;
                    }

                    res = myQuery(str);

                    log = mView.getText().toString();
                    log += str + " " + res + "\n";

                    mView.setText(log);
                    turn = 0;
                    typeView.setText("type nums you said");
                    break;
            }
        }
    }

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_number_baseball);

        // init
        enterButton = (Button) findViewById(R.id.enterButton);
        clearButton = (Button) findViewById(R.id.clearButton);

        sizeView = (TextView) findViewById(R.id.sizeView);
        mView = (TextView) findViewById(R.id.mView);
        yView = (TextView) findViewById(R.id.yView);
        typeView = (TextView) findViewById(R.id.type);

        stringText = (EditText) findViewById(R.id.editText);

        enterButton.setOnClickListener(new enterListener());
        clearButton.setOnClickListener(new clearListener());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void clear(String str);
    public native int size();
    public native String myQuery(String str);
    public native String yourQuery(String str);
    public native String whatNext();
}
