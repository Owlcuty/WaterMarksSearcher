import os

def rename_files(folder_path):
    # Получаем список всех файлов в папке
    files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]
    
    # Сортируем файлы (опционально, если нужно определенное упорядочивание)
    files.sort()
    
    # Переименовываем каждый файл
    for i, filename in enumerate(files, start=1):
        # Формируем новое имя файла
        new_name = f"negative_{i:03d}.png"
        
        # Полные пути к файлам
        old_path = os.path.join(folder_path, filename)
        new_path = os.path.join(folder_path, new_name)
        
        # Переименовываем файл
        os.rename(old_path, new_path)
        print(f"Переименован {filename} -> {new_name}")

# Укажите путь к вашей папке
folder_path = "dataset/train/negative/"
rename_files(folder_path)