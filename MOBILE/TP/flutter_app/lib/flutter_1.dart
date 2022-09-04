import 'package:flutter/material.dart';

void main(){
  runApp(
    MaterialApp(
      home: Scaffold(
        backgroundColor: Colors.blue,
        appBar: AppBar(
          title: Text('test'),
          backgroundColor: Colors.amber,
        ),
        body: Center(
          child: Image(
            image: AssetImage('Optima'),
          ),
        ),
      ),
    )
  );
}