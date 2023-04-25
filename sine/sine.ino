#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>

// sine_model.h contains the array you exported from Python with xxd or tinymlgen
#include "sine_model.h"
#include "math.h"

#define N_INPUTS 1
#define N_OUTPUTS 1
// in future projects you may need to tweak this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 2*1024

Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf;


void setup() {
    Serial.begin(115200);
    delay(4000);
    tf.begin(model_data);
    
    // check if model loaded fine
    if (!tf.isOk()) {
        Serial.print("ERROR: ");
        Serial.println(tf.getErrorMessage());
        
        while (true) delay(1000);
    }
}

void loop() {
    for (float i = 0; i < 360; i++) {
        // pick x from 0 to PI
        float x = 2 * 3.14 * i / 360;
        float input[1] = { x };
        float predicted = tf.predict(input);
        float actual = sin(x);
        Serial.print(predicted);
        Serial.print(",");
        Serial.println(actual);
        delay(100);
    }

    
}
