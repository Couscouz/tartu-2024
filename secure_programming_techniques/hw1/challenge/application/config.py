class Config(object):
    #SECRET_KEY = os.urandom(69)
    SECRET_KEY = "12345"

class ProductionConfig(Config):
    DEBUG = False

class DevelopmentConfig(Config):
    DEBUG = True

class TestingConfig(Config):
    TESTING = True