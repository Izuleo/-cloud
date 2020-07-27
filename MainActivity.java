package com.example.led;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class MainActivity extends AppCompatActivity {
    Button ledOnBtn;
    Button ledOffBtn;
    TextView textView;

    FirebaseDatabase database = FirebaseDatabase.getInstance(); //Firebase 연동
    DatabaseReference myRef = database.getReference("LED_STATUS"); //LED_STATUS 값 가져오기

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.InitializeView();
        this.SetListener();
    }

    public void InitializeView() {
        setTitle("LED Remote Control");

        ledOnBtn = (Button)findViewById(R.id.ledOnBtn);
        ledOffBtn = (Button)findViewById(R.id.ledOffBtn);
        textView = (TextView)findViewById(R.id.textView);

        //textView에 LED_STATUS값 출력
        textView.setText(myRef.getKey());
    }

    public  void SetListener() {
        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String ledState = (String) dataSnapshot.getValue(); //ledState에 저장
                textView.setText("LED is " + ledState);             // textView에 출력
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {
            }
        });

        //ON 클릭 시
        ledOnBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view)
            {
                textView.setBackgroundColor(Color.Blue); //Background => Blue
                myRef.setValue("ON");                   //DB값 "ON"
            }
        });

        //OFF 클릭 시
        ledOffBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view)
            {
                textView.setBackgroundColor(Color.Green); //Background => Green
                myRef.setValue("OFF");                    //DB값 "OFF"
            }
        });
    }
}