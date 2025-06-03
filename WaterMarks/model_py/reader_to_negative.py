import cv2
import os

def video_to_frames(video_path, output_folder, frame_skip=1):
    """
    Разбивает видео на кадры и сохраняет их с временной меткой в имени файла.
    
    :param video_path: Путь к видеофайлу
    :param output_folder: Папка для сохранения кадров
    :param frame_skip: Сохранять каждый N-ый кадр (по умолчанию 1 - все кадры)
    """
    # Создаем папку, если её нет
    os.makedirs(output_folder, exist_ok=True)
    
    # Открываем видео
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        print(f"Ошибка: Не удалось открыть видео {video_path}")
        return
    
    # Получаем FPS видео
    fps = cap.get(cv2.CAP_PROP_FPS)
    frame_count = 0
    saved_count = 0
    
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        # Сохраняем каждый frame_skip-ый кадр
        if frame_count % frame_skip == 0:
            # Вычисляем время текущего кадра в секундах
            current_time_sec = frame_count / fps
            # Форматируем время: часы_минуты_секунды_миллисекунды
            hours = int(current_time_sec // 3600)
            minutes = int((current_time_sec % 3600) // 60)
            seconds = int(current_time_sec % 60)
            milliseconds = int((current_time_sec - int(current_time_sec)) * 1000)
            
            time_str = f"{hours:02d}_{minutes:02d}_{seconds:02d}_{milliseconds:03d}"
            output_path = os.path.join(output_folder, f"source_{time_str}.png")
            
            cv2.imwrite(output_path, frame)
            saved_count += 1
            print(f"Сохранен кадр {output_path}")
        
        frame_count += 1
    
    cap.release()
    print(f"Готово! Сохранено {saved_count} кадров из {frame_count}")

# Пример использования
video_path = "D:\\projects\\WaterMarksSearcher\\example\\videoplayback.mp4"  # Укажите путь к вашему видео
output_folder = "dataset/train/negative"

# Сохранять каждый 10-й кадр (чтобы не было слишком много похожих кадров)
video_to_frames(video_path, output_folder, frame_skip=20)