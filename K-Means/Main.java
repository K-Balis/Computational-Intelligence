/*	------------ Exercise 2). K-Means Clustering ------------	*/

import java.util.*;
import java.io.*;

public class Main {

	private static ArrayList<double[]> dataset = new ArrayList<double[]>();
	private static ArrayList<double[]> outputDataset = new ArrayList<double[]>();
	private static ArrayList<double[]> outputMeans = new ArrayList<double[]>();
	
	public static void main(String[] args) {

		int[] M = {3, 6, 9, 12};	/*	Number of clusters for each loop	*/
		int[] numberofpoints = {150, 150, 150, 150, 150, 75, 75, 75, 75, 150};
		double[] x_min = {0.8, 0.0, 0.0, 1.5, 1.5, 0.8, 0.8, 0.3, 1.3, 0.0};
		double[] x_max = {1.2, 0.5, 0.5, 2.0, 2.0, 1.2, 1.2, 0.7, 1.7, 2.0};
		double[] y_min = {0.8, 0.0, 1.5, 0.0, 1.5, 0.0, 1.6, 0.8, 0.8, 0.0};
		double[] y_max = {1.2, 0.5, 2.0, 0.5, 2.0, 0.4, 2.0, 1.2, 1.2, 2.0};
		double currentError;
		double minError = Double.MAX_VALUE;
		
		/*	Create Random Points	*/
		for (int i = 0; i < numberofpoints.length; i++) {
			generateData(numberofpoints[i], x_min[i], x_max[i], y_min[i], y_max[i]);
		}
						
		for (int i = 0; i < M.length; i++) {
			try{
				String fileName = M[i] + "_clusters.txt";
				File file = new File(fileName);
				FileWriter fileWriter = new FileWriter(fileName);
				
				for (int j = 0; j < 15; j++) {		/*	We will execute K-means 15 times with random starting means	*/
					
					KMeans kmeans = new KMeans();
					kmeans.executeKMeansAlgorithm(M[i], dataset);		/*	Execute algorithm	*/
					currentError = kmeans.calculateError(M[i]);
					System.out.println("For "+M[i]+" clusters in loop " + (j+1) + " error = "+currentError);
					
					if (currentError < minError) {					/*	Keep information for minimum error	*/
						minError = currentError;
						outputDataset = kmeans.returnDataset();
						outputMeans = kmeans.returnMeans();
					}
				}
				/*	Write results in file	*/
				fileWriter.write(minError + "\n");
				for(double d[] : outputDataset){
					fileWriter.write(d[0] + " " + d[1] + " " + d[2] + "\n");
				}
				
				for(double m[] : outputMeans){
					fileWriter.write(m[0] + " " + m[1] + "\n");
				}
				fileWriter.close();
				System.out.println(M[i] + "_clusters.txt" + " was created");
			}
			catch (IOException e){ 
                System.out.println("Error!");
                e.printStackTrace();
            }
		}
	}	

	private static void generateData(int number_of_points, double x_min, double x_max, double y_min, double y_max) {
		
		for (int i = 0; i < number_of_points; i++) {
			double x_of_new_point = Math.random() * (x_max - x_min) + x_min;
			double y_of_new_point = Math.random() * (y_max - y_min) + y_min;
			double[] newPoint = {x_of_new_point, y_of_new_point};
			dataset.add(newPoint);
		}
	}
}
