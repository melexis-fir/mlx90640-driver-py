from .mlx90640 import MLX90640

__import__('pkg_resources').declare_namespace(__name__)


__version__ = '1.1.2'


# try to pre-load our 3 default I2C low level implementations!

try:
	import mlx90640_evb9064x
except Exception as e:
	pass

try:
	import mlx90640_mcp2221
except Exception as e:
	pass

try:
	import mlx90640_devicetree
except Exception as e:
	pass

