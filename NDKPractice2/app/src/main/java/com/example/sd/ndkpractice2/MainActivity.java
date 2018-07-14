package com.example.sd.ndkpractice2;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;
import java.lang.String;

public class MainActivity extends AppCompatActivity  {
    private EditText numA, numB, keyText, strText;
    private TextView text, resultText;
    private Store mStore;
    private Button UImulButton, UIsumButton, UIsetButton, UIgetButton;


    public class UImulListener implements Button.OnClickListener {
        @Override
        public void onClick(View v){
           int a = Integer.parseInt(numA.getText().toString());
           int b = Integer.parseInt(numB.getText().toString());

           int res = mStore.mul(a, b);
            //int res = a * b;
           text.setText(String.valueOf(res));
        }
    }
    public class UIsumListener implements Button.OnClickListener {
        @Override
        public void onClick(View v){
            int a = Integer.parseInt(numA.getText().toString());
            int b = Integer.parseInt(numB.getText().toString());

            int res = mStore.add(a, b);
            //int res = a + b;
            text.setText(String.valueOf(res));
        }
    }

    public class UIsetListener implements Button.OnClickListener {
        @Override
        public void onClick(View v){
            String str = strText.getText().toString();
            int key = Integer.parseInt(keyText.getText().toString());

            mStore.setString(key, str);
            resultText.setText("store! " + str);
        }
    }

    public class UIgetListener implements Button.OnClickListener {
        @Override
        public void onClick(View v){
            int key = Integer.parseInt(keyText.getText().toString());

            String str = mStore.getString(key);

            resultText.setText(str);
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        //init
       numA = (EditText) findViewById(R.id.textA);
        numB = (EditText) findViewById(R.id.textB);

         text = (TextView) findViewById(R.id.textView);
        mStore = new Store();

        UImulButton = (Button) findViewById(R.id.mButton);
        UIsumButton = (Button) findViewById(R.id.sumButton);

        UIsetButton = (Button) findViewById(R.id.setEnter);
        UIgetButton = (Button) findViewById(R.id.getEnter);

        keyText = (EditText) findViewById(R.id.Key);
        strText = (EditText) findViewById(R.id.strArea);
        resultText = (TextView) findViewById(R.id.resultText);

        UImulButton.setOnClickListener(new UImulListener());
        UIsumButton.setOnClickListener(new UIsumListener());
        UIsetButton.setOnClickListener(new UIsetListener());
        UIgetButton.setOnClickListener(new UIgetListener());
    }
}
