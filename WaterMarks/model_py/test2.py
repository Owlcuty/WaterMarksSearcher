# test_onnx_fixed.py
import cv2
import numpy as np

def test_onnx_model():
    # 1. Загрузка модели
    net = cv2.dnn.readNetFromONNX("watermark_detector.onnx")
    if net.empty():
        raise ValueError("Failed to load ONNX model")
    
    # 2. Получаем реальные имена входов
    input_names = net.getUnconnectedOutLayersNames()
    print("Actual input names:", input_names)
    
    # 3. Если модель не возвращает имена, попробуем стандартные:
    try:
        input_a_name = "input_a:0"  # Попробуем стандартное имя
        input_b_name = "input_b:0"
        
        # 4. Подготовка тестовых данных
        watermark = np.random.rand(128, 128, 1).astype(np.float32)
        frame = np.random.rand(128, 128, 1).astype(np.float32)
        
        # 5. Создание blob-ов
        wm_blob = cv2.dnn.blobFromImage(watermark, scalefactor=1.0, size=(128, 128))
        fr_blob = cv2.dnn.blobFromImage(frame, scalefactor=1.0, size=(128, 128))
        
        # 6. Установка входов
        net.setInput(wm_blob, input_a_name)
        net.setInput(fr_blob, input_b_name)
        
        # 7. Запуск модели
        output = net.forward()
        print(f"Prediction: {output[0][0]:.4f}")
        
    except Exception as e:
        print(f"Error: {e}")
        print("Try to inspect model with Netron: https://github.com/lutzroeder/netron")

if __name__ == "__main__":
    test_onnx_model()