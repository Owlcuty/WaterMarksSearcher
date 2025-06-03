import tensorflow as tf
import tf2onnx

# Загружаем модель
model = tf.keras.models.load_model("watermark_finetunedNew.h5")

# Прописываем вход явно
input_spec = (tf.TensorSpec((1, 224, 224, 3), tf.float32, name="input_1"),)

# Конвертируем в ONNX с каналами первым (NCHW)
onnx_model, _ = tf2onnx.convert.from_keras(
    model,
    input_signature=input_spec,
    opset=13,
    output_path="model.onnx",
    inputs_as_nchw=["input_1"]
)

print("✅ Сконвертировано в NCHW → model.onnx")
