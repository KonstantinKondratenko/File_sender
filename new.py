import pybullet as p
import time
import numpy as np

# Инициализация симуляции
p.connect(p.GUI)
p.setGravity(0, 0, -10)

# Создание плоскости для листа бумаги
planeId = p.loadURDF("plane.urdf", [0,0,-0.1])

# Создание листа бумаги
paperId = p.loadURDF("paper.urdf", [0, 0, 5])

# Начальные параметры листа бумаги
position = [0, 0, 5]
orientation = p.getQuaternionFromEuler([0, 0, 0])
p.resetBasePositionAndOrientation(paperId, position, orientation)

# Симуляция падения и планирования листа бумаги
for _ in range(10000):
    p.stepSimulation()
    time.sleep(1./48.)

    # Пример применения случайной силы и момента к листу бумаги
    force = np.random.uniform(-1, 1, size=3)
    torque = np.random.uniform(-1, 1, size=3)
    p.applyExternalForce(paperId, -1, force, [0, 0, 0], p.LINK_FRAME)
    p.applyExternalTorque(paperId, -1, torque, flags=p.WORLD_FRAME)

    # Создание подъемной силы для планирования
    linearVel, angularVel = p.getBaseVelocity(paperId)
    liftForce = [0, 0, max(0, 0.05 * linearVel[2])]  # Коэффициент подъема 0.05
    p.applyExternalForce(paperId, -1, liftForce, [0, 0, 0], p.LINK_FRAME)

# Завершение симуляции
p.disconnect()