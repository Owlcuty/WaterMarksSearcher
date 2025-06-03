from tensorflow.keras.models import load_model
import cv2

model = load_model("watermark_classifier.h5")
test_img = cv2.imread("dataset/train/positive/frame10000.png", cv2.IMREAD_GRAYSCALE)
test_img_resized = cv2.resize(test_img, (128,128)) / 255.0
test_input = test_img_resized.reshape(1,128,128,1)

prediction = model.predict(test_input)
if prediction[0][0] > 0.5:
    print("Обнаружен водяной знак")
else:
    print("Водяной знак не обнаружен")