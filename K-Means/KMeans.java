import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;

public class KMeans {
	
	private ArrayList<double[]> data = new ArrayList<double[]>();
	private ArrayList<double[]> updatedData = new ArrayList<double[]>();
	private ArrayList<double[]> means = new ArrayList<double[]>();
	private ArrayList<double[]> previousPosOfMeans = new ArrayList<double[]>();
	
	int numberOfClusters;
	int newStartingMeanPos;
	boolean PointHasNotBeenUsedAsMean = true;
	int twoRepetitions = 0;
	
	public void executeKMeansAlgorithm(int numberOfClusters, ArrayList<double[]> data) {
		this.numberOfClusters = numberOfClusters;
		this.data = data;
		
		int[] previousStartingMeans = new int[numberOfClusters];

		/*			Initialize Means			*/
		for (int i = 0; i < numberOfClusters; i++) {
			while(true) {		/*	Make sure each starting mean is unique	*/
				newStartingMeanPos = ThreadLocalRandom.current().nextInt(0, 1200);
				for (int j = 0; j < previousStartingMeans.length; j++) {
					if (previousStartingMeans[j] == newStartingMeanPos) {
						PointHasNotBeenUsedAsMean = false;
					}
				}
				if(PointHasNotBeenUsedAsMean) {
					break;
				}
			}
			previousStartingMeans[i] = newStartingMeanPos;
			double[] newMean = data.get(newStartingMeanPos);
			double x = newMean[0];
			double y = newMean[1];
			double[] meanpos = {x,y};
 			means.add(meanpos);			/*	Store new mean	*/
		}

		/*			Add data to Clusters		*/
		while (true) {
			updatedData.clear();
			for (int i = 0; i < data.size(); i++) {
				double minDistance = Double.MAX_VALUE;
				double closestCluster = -1;
				for (int j = 0; j < numberOfClusters; j++) {
					double distance = computeEuclidianDistance(i, j);
					if (distance < minDistance) {
						minDistance = distance;
						closestCluster = j;
					}
				}

				double[] dataWithClosestCluster = {data.get(i)[0], data.get(i)[1], (double) closestCluster};
				updatedData.add(dataWithClosestCluster);
			}
			previousPosOfMeans.clear();
			for (int i = 0; i < means.size(); i++) {					/*	Before the update of means we keep a copy of previous positions so we can check for termination	*/
				double[] getMeanPosition = {means.get(i)[0], means.get(i)[1]};
				previousPosOfMeans.add(getMeanPosition);
			}
			for (int i = 0; i < numberOfClusters; i++) {				/*	Update Means  */
				double x_pos = 0.0;
				double y_pos = 0.0;
				int dataincluster = 0;
				for (int j = 0; j < updatedData.size(); j++) {
					if (updatedData.get(j)[2] == i) {
						dataincluster++;
						x_pos += updatedData.get(j)[0];
						y_pos += updatedData.get(j)[1];
					}
				}
				means.get(i)[0] = x_pos / dataincluster;
				means.get(i)[1] = y_pos / dataincluster;
			}
			int meanVectorsHaveNotChanged = 0;					/*	Check for termination	*/
			for (int i = 0; i < numberOfClusters; i++) {
				if(	(means.get(i)[0] == previousPosOfMeans.get(i)[0]) && (means.get(i)[1] == previousPosOfMeans.get(i)[1]) ) {
					meanVectorsHaveNotChanged++; 					/*	if we detect change in a mean's position we shouldn't allow termination	*/
				}
				else {
					twoRepetitions = 0;
				}
			}
			if (meanVectorsHaveNotChanged == numberOfClusters  && twoRepetitions >=2) {		/*	This condition must be true so we can allow termination (no changes between two repetitions of the algorithm)	*/
				break;
			}
			else if (meanVectorsHaveNotChanged == numberOfClusters && twoRepetitions <2){
				twoRepetitions++;
			}
 		}
	}
	
	public double computeEuclidianDistance(int newdata, int cluster) {
		double[] datapos = data.get(newdata);
		double[] clusterpos = means.get(cluster);
		return Math.sqrt(Math.pow(datapos[0] - clusterpos[0],2) + Math.pow(datapos[1] - clusterpos[1],2));
	}
	
	public double calculateError(int numOfClusters) {
		double error = 0.0;
		for (int i = 0; i < numOfClusters; i++) {
			for (int j = 0; j < updatedData.size(); j++) {
				if (updatedData.get(j)[2] == i) {
					error += computeEuclidianDistance(j, i);
				}
			}
		}
		return error;
	}

	public ArrayList<double[]> returnDataset() {
		return updatedData;
	}

	public ArrayList<double[]> returnMeans() {
		return means;
	}

}
