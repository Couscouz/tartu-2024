from application.database import query_db, populate_db
from werkzeug.security import generate_password_hash

class school(object):
    
    @staticmethod
    def select_by_email(email):
        return query_db(f"SELECT * FROM users WHERE email='{email}'")  

    @staticmethod
    def all_users():
        return query_db('SELECT email FROM users')    
        
    @staticmethod
    def create_new_user(email, password, isadmin=False):
        return populate_db(f'INSERT INTO users (email, password, isadmin) VALUES(?,?,?)', (email, generate_password_hash(password), isadmin))
    
    @staticmethod
    def delete_jwt_token(token):
        return
    
    @staticmethod
    def delete_user(user_id):
        return populate_db(f"DELETE FROM users WHERE id = ?", user_id)
    
    @staticmethod
    def add_grade(grade, subject, description, user_id):
        return populate_db(f'INSERT INTO grades (grade, subject, description, user_id) VALUES(?,?,?,?)', (int(grade), subject, description, user_id))

    @staticmethod
    def delete_grade(user_id):
        return populate_db(f"DELETE FROM grades WHERE id = (SELECT MAX(id) FROM grades WHERE user_id = ?)", (user_id,))
    
    @staticmethod
    def get_grades(user_id):
        return query_db(f"SELECT grade, subject, description FROM grades WHERE user_id = ?", (user_id, ))