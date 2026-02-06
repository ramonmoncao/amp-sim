import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from loadDataSet import build
import tf2onnx

if __name__ == "__main__":
    
    X, Y = build("dataset.txt")

    model = Sequential([
        tf.keras.layers.Dense(16, activation="tanh", input_shape=(1,)),
        tf.keras.layers.Dense(16, activation="tanh"),
        tf.keras.layers.Dense(1, activation="linear")
    ])

    model.compile(
        optimizer=tf.keras.optimizers.Adam(1e-3),
        loss="mse"
    )
    
    history = model.fit(
        X, Y,
        epochs=500,
        batch_size=32,
        validation_split=0.1,
        shuffle=True, 
    )

    spec = (tf.TensorSpec((None, 1), tf.float32, name="input"),)
    
    @tf.function
    def predict_fn(x):
        return model(x)

    model_proto, _ = tf2onnx.convert.from_function(
        predict_fn, 
        input_signature=spec, 
        opset=13,
        output_path="triode_model.onnx"
    )
