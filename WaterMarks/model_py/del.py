import os
import random
import shutil

def delete_random_files(folder_path, num_files_to_delete=400, move_to_trash=False):
    """
    Удаляет случайные файлы из указанной папки
    
    :param folder_path: Путь к папке с файлами
    :param num_files_to_delete: Сколько файлов удалить
    :param move_to_trash: Если True - перемещает в корзину вместо удаления
    """
    # Получаем список всех файлов (только PNG для примера)
    all_files = [f for f in os.listdir(folder_path) 
                if f.lower().endswith('.png') and f.startswith('source_')]
    
    if len(all_files) <= num_files_to_delete:
        print(f"Ошибка: В папке только {len(all_files)} файлов, нельзя удалить {num_files_to_delete}")
        return
    
    # Выбираем случайные файлы для удаления
    files_to_delete = random.sample(all_files, num_files_to_delete)
    
    # Создаем папку для "корзины", если нужно
    trash_folder = os.path.join(folder_path, "_trash")
    if move_to_trash:
        os.makedirs(trash_folder, exist_ok=True)
    
    deleted_count = 0
    for filename in files_to_delete:
        file_path = os.path.join(folder_path, filename)
        
        try:
            if move_to_trash:
                # Перемещаем в корзину
                shutil.move(file_path, os.path.join(trash_folder, filename))
            else:
                # Полное удаление
                os.remove(file_path)
            
            deleted_count += 1
            print(f"Удален: {filename}")
        except Exception as e:
            print(f"Ошибка при удалении {filename}: {str(e)}")
    
    print(f"\nУдалено {deleted_count}/{num_files_to_delete} файлов")
    if move_to_trash:
        print(f"Файлы перемещены в: {trash_folder}")

if __name__ == "__main__":
    # Настройки
    negative_folder = "dataset/train/negative"
    files_to_delete = 400  # Сколько файлов удалить
    use_trash = False  # Перемещать в корзину вместо удаления
    
    # Запуск
    delete_random_files(negative_folder, files_to_delete, move_to_trash=use_trash)