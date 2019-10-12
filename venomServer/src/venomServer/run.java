package venomServer;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import lejos.hardware.Button;
import lejos.hardware.Key;
import lejos.hardware.KeyListener;
import lejos.hardware.lcd.LCD;
import lejos.hardware.motor.Motor;
import lejos.robotics.RegulatedMotor;

public class run {

	static int angle = 270; // 馬達轉動的角度
	
//	static int speed = 500;
	static int speed = 800;

	private static boolean OutServer = false;
	private static ServerSocket server;
	private final static int ServerPort = 1234; // 要監控的port

	public static void main(String[] args) {

		//按下ESCAPE鍵離開程式
		Button.ESCAPE.addKeyListener(new KeyListener() {
			public void keyReleased(Key k) {
				System.exit(0);
			}
			public void keyPressed(Key k) {
				System.exit(0);
			}
		});

		print("Start");
		
		Thread socketServer_thread = new Thread(socketServer_runnable);
		socketServer_thread.start();
	}

	//建立SocketServer
	public static void SocketServer() {
		try {
			server = new ServerSocket(ServerPort);

		} catch (java.io.IOException e) {
			print("Socket Error!");
			print("IOException :" + e.toString());
		}
	}

	static Runnable socketServer_runnable = new Runnable() {
		public void run() {
			SocketServer();

			Socket socket;

			print("Socket Server OK!");

			while (!OutServer) {
				socket = null;
				do {
					try {
						synchronized (server) {
							socket = server.accept();
						}
						print(socket.getInetAddress().toString()); //印出目前連線設備的ip

						//Socket接收
						BufferedReader inbound = new BufferedReader(
								new InputStreamReader(socket.getInputStream()));

						//Socket發送
						PrintWriter outbound = new PrintWriter(
								socket.getOutputStream(), true);

						while (true) {
							String data = "";

							outbound.println("Success");

							while ((data = inbound.readLine()) == null);

							if (data.length()>=3)
								print("getData:" + data);

							if (data.equals("FWD")) {
								go();
								outbound.print(data + " OK");
							} else if (data.equals("BACK")) {
								back();
								outbound.print(data + " OK");
							} else if (data.equals("LEFT")) {
								left();
								outbound.print(data + " OK");
							} else if (data.equals("RIGHT")) {
								right();
								outbound.print(data + " OK");
							} else if (data.equals("STOP")) {
								stop();
								outbound.print(data + " OK");
							} else if (data.equals("HOLD")) {
								hold();
								outbound.print(data + " OK");
							}  else if (data.equals("FLATTEN")) {
								flatten();
								outbound.print(data + " OK");
							}  else if (data.equals("PULL")) {
								pull();
								outbound.print(data + " OK");
							}  else if (data.equals("PUT")) {
								put();
								outbound.print(data + " OK");
							} else if (data.equals("STOP_PUT") || data.equals("STOP_PULL")) {
								stopC();
								outbound.print(data + " OK");
							} else if (data.equals("STOPB")) {
								stopB();
								outbound.print(data + " OK");
							}
						}

					} catch (java.io.IOException e) {
						print("Socket Error");
						print("IOException :" + e.toString());
						Thread socketServer_thread = new Thread(socketServer_runnable);
						socketServer_thread.start();
					}
				} while (!socket.isConnected());

			}
		}
	};
	
	//前進
	private static void go() {
		Motor.A.synchronizeWith(new RegulatedMotor[]{Motor.D});
		Motor.A.setSpeed(speed);
		Motor.D.setSpeed(speed);
		Motor.A.backward();
		Motor.D.backward();
	}

	//後退
	private static void back() {
//		Motor.A.backward();
//		Motor.A.backward();
		Motor.A.synchronizeWith(new RegulatedMotor[]{Motor.D});
		Motor.A.setSpeed(speed);
		Motor.D.setSpeed(speed);
		Motor.A.forward();
		Motor.D.forward();
	}

	private static void left() {
		Motor.A.synchronizeWith(new RegulatedMotor[]{Motor.D});
		Motor.A.setSpeed(300);
		Motor.D.setSpeed(300);
		Motor.A.backward();
		Motor.D.forward();
	}
	
	private static void right() {
		Motor.A.synchronizeWith(new RegulatedMotor[]{Motor.D});
		Motor.A.setSpeed(300);
		Motor.D.setSpeed(300);
		Motor.A.forward();
		Motor.D.backward();
	}
	
//	//左轉
//	private static void left(int angle) {		
//		Motor.A.rotate(-angle, true);
//		Motor.A.rotate(angle, true);
//		
//	}
//
//	//右轉
//	private static void right(int angle) {
//		Motor.A.rotate(angle, true);
//		Motor.A.rotate(-angle, true);
//	}

	//停止
	private static void stop() {
	    Motor.A.endSynchronization();
		Motor.A.stop(true);
		Motor.D.stop(true);
		
//	    Motor.A.setSpeed(0);
//	    Motor.A.setSpeed(0);
	}
	
	private static void stopB() {
		Motor.B.stop(true);
	}
	
	private static void stopC() {
		Motor.C.stop(true);
	}
	
	private static void pull() {
		Motor.C.setSpeed(350);
		Motor.C.backward();
//		Motor.C.rotateTo(90);
	}
	
	private static void put() {
		Motor.C.setSpeed(350);
		Motor.C.forward();
//		Motor.C.rotateTo(0);
	}
	
	private static void hold() { //上半場speed,下半場200
		Motor.B.setSpeed(150);
		Motor.B.forward();
	}
	
	private static void flatten() { //上半場speed,下半場200
		Motor.B.setSpeed(150);
		Motor.B.backward();
	}

	//在EV3螢幕印出字串
	private static void print(String str) {
		LCD.clear();
		LCD.drawString(str, 0, 3);
	}

}