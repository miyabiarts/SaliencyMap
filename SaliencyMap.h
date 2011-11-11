#pragma once

#include <opencv2/opencv.hpp>

//
template< typename T = double >
class SaliencyMap
{
	typedef cv::Mat_< T > Matrix;

public:
	SaliencyMap()
	{
		// ガボールフィルタ用の行列を用意
		gaborKernel_0 = ( Matrix( 9, 9 ) << 
			1.85212e-06,	1.28181e-05,	-0.000350433,	-0.000136537,	0.002010422,	-0.000136537,	-0.000350433, 1.28181e-05,	1.85212e-06,
			2.80209e-05,	0.000193926,	-0.005301717,	-0.002065674,	0.030415784,	-0.002065674,	-0.005301717, 0.000193926,	2.80209e-05,
			0.000195076,	0.001350077,	-0.036909595,	-0.014380852,	0.211749204,	-0.014380852,	-0.036909595, 0.001350077,	0.000195076,
			0.00062494,	0.004325061,	-0.118242318,	-0.046070008, 0.678352526,	-0.046070008,	-0.118242318,	0.004325061, 0.00062494,
			0.000921261,	0.006375831,	-0.174308068,	-0.067914552,	1,	 -0.067914552,	-0.174308068, 0.006375831,	0.000921261,
			0.00062494,	0.004325061,	-0.118242318,	-0.046070008, 0.678352526,	-0.046070008,	-0.118242318,	0.004325061, 0.00062494,
			0.000195076,	0.001350077,	-0.036909595,	-0.014380852,	0.211749204,	-0.014380852,	-0.036909595, 0.001350077,	0.000195076,
			2.80209e-05,	0.000193926,	-0.005301717,	-0.002065674,	0.030415784,	-0.002065674,	-0.005301717, 0.000193926,	2.80209e-05,
			1.85212e-06,	1.28181e-05,	-0.000350433,	-0.000136537,	0.002010422,	-0.000136537,	-0.000350433, 1.28181e-05,	1.85212e-06);

		gaborKernel_45 = ( Matrix( 9, 9 ) << 
			4.0418e-06,	2.2532e-05,	 -0.000279806,	-0.001028923, 3.79931e-05,	0.000744712,	0.000132863,	-9.04408e-06,	-1.01551e-06,
			2.2532e-05,	0.00092512,	 0.002373205,	-0.013561362,	-0.0229477,	 0.000389916,	0.003516954	,	0.000288732,	-9.04408e-06,
			-0.000279806,	0.002373205,	0.044837725,	0.052928748, -0.139178011,	-0.108372072,	0.000847346	, 0.003516954,	0.000132863,
			-0.001028923,	-0.013561362,	0.052928748,	0.46016215, 0.249959607,	-0.302454279,	-0.108372072,	0.000389916, 0.000744712,
			3.79931e-05,	-0.0229477,	 -0.139178011,	0.249959607, 1,	 0.249959607,	-0.139178011,	-0.0229477,	 3.79931e-05,
			0.000744712,	0.000389916,	-0.108372072,	-0.302454279,	0.249959607,	0.46016215,	 0.052928748,	-0.013561362,	-0.001028923,
			0.000132863,	0.003516954,	0.000847346,	-0.108372072, -0.139178011,	0.052928748,	0.044837725,	0.002373205, -0.000279806,
			-9.04408e-06,	0.000288732,	0.003516954,	0.000389916, -0.0229477,	 -0.013561362,	0.002373205,	0.00092512, 2.2532e-05,
			-1.01551e-06,	-9.04408e-06,	0.000132863, 0.000744712,	3.79931e-05,	-0.001028923,	-0.000279806, 2.2532e-05,	 4.0418e-06);


		gaborKernel_90 = ( Matrix( 9, 9 ) << 
			1.85212e-06,	2.80209e-05,	0.000195076,	0.00062494, 0.000921261,	0.00062494,	 0.000195076,	2.80209e-05, 1.85212e-06,
			1.28181e-05,	0.000193926,	0.001350077,	0.004325061, 0.006375831,	0.004325061,	0.001350077,	0.000193926, 1.28181e-05,
			-0.000350433,	-0.005301717,	-0.036909595,	-0.118242318,	-0.174308068,	-0.118242318,	-0.036909595,	-0.005301717,	-0.000350433,
			-0.000136537,	-0.002065674,	-0.014380852,	-0.046070008,	-0.067914552,	-0.046070008,	-0.014380852,	-0.002065674,	-0.000136537,
			0.002010422,	0.030415784,	0.211749204,	0.678352526, 1,	 0.678352526,	0.211749204,	0.030415784, 0.002010422,
			-0.000136537,	-0.002065674,	-0.014380852,	-0.046070008,	-0.067914552,	-0.046070008,	-0.014380852,	-0.002065674,	-0.000136537,
			-0.000350433,	-0.005301717,	-0.036909595,	-0.118242318,	-0.174308068,	-0.118242318,	-0.036909595,	-0.005301717,	-0.000350433,
			1.28181e-05,	0.000193926,	0.001350077,	0.004325061, 0.006375831,	0.004325061,	0.001350077,	0.000193926, 1.28181e-05,
			1.85212e-06,	2.80209e-05,	0.000195076,	0.00062494, 0.000921261,	0.00062494,	 0.000195076,	2.80209e-05, 1.85212e-06);

	

		gaborKernel_135 = ( Matrix( 9, 9 ) << 
			-1.01551e-06,	-9.04408e-06,	0.000132863, 0.000744712,	3.79931e-05,	-0.001028923,	-0.000279806, 2.2532e-05,	 4.0418e-06,
			-9.04408e-06,	0.000288732,	0.003516954,	0.000389916, -0.0229477,	 -0.013561362,	0.002373205,	0.00092512, 2.2532e-05,
			0.000132863,	0.003516954,	0.000847346,	-0.108372072, -0.139178011,	0.052928748,	0.044837725,	0.002373205, -0.000279806,
			0.000744712,	0.000389916,	-0.108372072,	-0.302454279,	0.249959607,	0.46016215,	 0.052928748,	-0.013561362,	-0.001028923,
			3.79931e-05,	-0.0229477,	 -0.139178011,	0.249959607, 1,	 0.249959607,	-0.139178011,	-0.0229477,	 3.79931e-05,
			-0.001028923,	-0.013561362,	0.052928748,	0.46016215, 0.249959607	,	-0.302454279,	-0.108372072, 0.000389916,	0.000744712,
			-0.000279806,	0.002373205,	0.044837725,	0.052928748, -0.139178011,	-0.108372072,	0.000847346,	0.003516954, 0.000132863,
			2.2532e-05,	0.00092512,	 0.002373205,	-0.013561362,	-0.0229477,	 0.000389916,	0.003516954,	0.000288732,	-9.04408e-06,
			4.0418e-06,	2.2532e-05,	 -0.000279806,	-0.001028923, 3.79931e-05	,	0.000744712,	0.000132863,	-9.04408e-06, -1.01551e-06);
	

		// 各特徴マップの重みの初期値を設定
		weightIntensity = 0.3;
		weightColor = 0.2;
		weightOrientation = 0.2;
		weightMotion = 0.2;

		stepLocalMaxima = 8;
	}

	~SaliencyMap()
	{

	}

	// SaliencyMapを計算
	Matrix compute( const cv::Mat_< cv::Vec3b > &in )
	{
		int w = in.cols;
		int h = in.rows;

		// 各成分への分割
		std::vector< cv::Mat_< unsigned char > > bgr0;
		cv::split( in, bgr0 );

		// グレースケール画像への変換
		cv::Mat_< unsigned char > gray0;
		cv::cvtColor( in, gray0, CV_BGR2GRAY );
			
		// 浮動小数に変換・0-1に正規化
		std::vector< Matrix > bgr( 3 );
		for( int i = 0 ; i < 3 ; ++i )
		{
			bgr[ i ] = Matrix( h, w );
			std::copy( bgr0[ i ].begin(), bgr0[ i ].end(), bgr[ i ].begin() );
			bgr[ i ] /= 255.0;
		}
		
		Matrix gray( h, w );
		std::copy( gray0.begin(), gray0.end(), gray.begin() );
		gray /= 255.0;

		
		// Intensity feature maps
		std::vector< Matrix > ifm;
		computeIntensityMap( gray, ifm );
		
		// Color feature map
		std::vector< Matrix > cfm_rg;
		std::vector< Matrix > cfm_by;
		computeColorMap( bgr, cfm_rg, cfm_by );

		// Orientation feature maps
		std::vector< Matrix > ofm;
		computeOrientationMap( gray, ofm );

		// Motion feature maps
		std::vector< Matrix > mfm_x;
		std::vector< Matrix > mfm_y;
		
		// Generate conspiculty map
		Matrix icm = createConspicuityMapFromIntensityMap( ifm, cv::Size( w, h ) );
		Matrix ccm = createConspicuityMapFromColorMap( cfm_rg, cfm_by, cv::Size( w, h ) );
		Matrix ocm = createConspicuityMapFromOrientationMap( ofm, cv::Size( w, h ) );
		
		// Saliency
		Matrix result = Matrix::zeros( h, w );
		cv::addWeighted( icm, weightIntensity, ocm, weightOrientation, 0.0, result );
		cv::addWeighted( ccm, weightColor, result, 1.0, 0.0, result );

		return normalizeMap( result );
	}

private:
	// ガボールフィルタ用の行列
	Matrix gaborKernel_0;
	Matrix gaborKernel_45;
	Matrix gaborKernel_90;
	Matrix gaborKernel_135;

	// 各特徴マップの重み
	T weightIntensity;
	T weightColor;
	T weightOrientation;
	T weightMotion;

	// 極大値探索の飛ばし幅
	int stepLocalMaxima;

	//
	void computeIntensityMap( const Matrix &in, std::vector< Matrix > &ifm )
	{
		ifm = computeGaussianMap( in );
	}

	//
	void computeColorMap( const std::vector< Matrix > &bgr, std::vector< Matrix > &cfm_rg, std::vector< Matrix > &cfm_by )
	{
		//
		Matrix rgbMax = cv::max( 1e-4, cv::max( cv::max( bgr[ 0 ], bgr[ 1 ] ), bgr[ 2 ] ) );
		Matrix rgMin = cv::min( bgr[ 1 ], bgr[ 2 ] );
		
		Matrix rgMat = cv::max( 0, ( bgr[ 2 ] -  bgr[ 1 ] ) / rgbMax );
		Matrix byMat = cv::max( 0, ( bgr[ 0 ] -  rgMin ) / rgbMax );

		cfm_rg = computeGaussianMap( rgMat );
		cfm_by = computeGaussianMap( byMat );
	}

	//
	void computeOrientationMap( const Matrix &in, std::vector< Matrix > &ofm )
	{
		// Create Gaussan map
		std::vector< Matrix > gaussian = createGaussianMatrix( in );

		std::vector< Matrix > gaborOutput_0( 9 );
		std::vector< Matrix > gaborOutput_45( 9 );
		std::vector< Matrix > gaborOutput_90( 9 );
		std::vector< Matrix > gaborOutput_135( 9 );
		for( int i = 2 ; i < 9 ; ++i )
		{
			cv::filter2D( gaussian[ i ], gaborOutput_0[ i ], -1, gaborKernel_0 );
			cv::filter2D( gaussian[ i ], gaborOutput_45[ i ], -1, gaborKernel_45 );
			cv::filter2D( gaussian[ i ], gaborOutput_90[ i ], -1, gaborKernel_90 );
			cv::filter2D( gaussian[ i ], gaborOutput_135[ i ], -1, gaborKernel_135 );
		}

		std::vector< Matrix > temp0 = computeDifferenceSurroundCenter( gaborOutput_0 );
		std::vector< Matrix > temp45 = computeDifferenceSurroundCenter( gaborOutput_45 );
		std::vector< Matrix > temp90 = computeDifferenceSurroundCenter( gaborOutput_90 );
		std::vector< Matrix > temp135 = computeDifferenceSurroundCenter( gaborOutput_135 );

		ofm.resize( 24 );
		for( int i = 0 ; i < 6 ; ++i )
		{
			ofm[ i ] = temp0[ i ];
			ofm[ 6 + i ] = temp45[ i ];
			ofm[ 12 + i ] = temp90[ i ];
			ofm[ 18 + i ] = temp135[ i ];
		}
	}

	//
    void computeMotionMap( const Matrix &in, std::vector< Matrix > &mfm_x, std::vector< Matrix > &mfm_y )
	{	
	}

	//
	std::vector< Matrix > computeGaussianMap( const Matrix in )
	{
		// Create Gaussan map
		std::vector< Matrix > gaussian = createGaussianMatrix( in );

		// Compute difference surround center		
		return computeDifferenceSurroundCenter( gaussian );
	}

	//
	std::vector< Matrix > createGaussianMatrix( const Matrix in )
	{
		std::vector< Matrix > gaussian( 9 );
		gaussian[ 0 ] = in.clone();
		for( size_t i = 1 ; i < 9 ; ++i )
		{
			cv::pyrDown( gaussian[ i - 1 ], gaussian[ i ] );
		}
		return gaussian;
	}

	//
	std::vector< Matrix > computeDifferenceSurroundCenter( std::vector< Matrix > &gaussian )
	{
		std::vector< Matrix > out( 6 );
		int level = 0;
		for( int i = 2 ; i < 5 ; ++i )
		{
			int w = gaussian[ i ].cols;
			int h = gaussian[ i ].rows;

			Matrix tmp;
			cv::resize( gaussian[ i + 3 ], tmp, cv::Size( w, h ) );	
			cv::absdiff( gaussian[ i ], tmp, out[ level ] );

			cv::resize( gaussian[ i + 4 ], tmp, cv::Size( w, h ) );
			cv::absdiff( gaussian[ i ], tmp, out[ level + 1 ] );			

			level += 2;
		}
		return out;
	}

	//
	Matrix createConspicuityMap( const std::vector< Matrix > &fm, const cv::Size &size )
	{
		std::vector< Matrix > nfm = normalizeMaps( fm, size.width, size.height );
		Matrix cm = Matrix::zeros( size.height, size.width );
		for( size_t i = 0 ; i < nfm.size() ; ++i )
		{
			cm += nfm[ i ];
		}
		return cm;
	}

	//
	Matrix createConspicuityMapFromIntensityMap( const std::vector< Matrix > &ifm, const cv::Size &size )
	{		
		return normalizeMap( createConspicuityMap( ifm, size ) );

	}

	//
	Matrix createConspicuityMapFromColorMap( const std::vector< Matrix > &cm_rg ,const std::vector< Matrix > &cm_by, const cv::Size &size )
	{
		return normalizeMap( createConspicuityMap( cm_rg, size ) + createConspicuityMap( cm_by, size ) ); 
	}

	//
	Matrix createConspicuityMapFromOrientationMap( const std::vector< Matrix > &ofm, const cv::Size &size )
	{
		return normalizeMap( createConspicuityMap( ofm, size ) );
	}

	//
	std::vector< Matrix > normalizeMaps( const std::vector< Matrix > &fmaps, int width, int height )
	{
		std::vector< Matrix > nfmaps( fmaps.size() );
		for( size_t i = 0 ; i < fmaps.size() ; ++i )
		{
			cv::resize( normalizeMapWithLocalMaxima( fmaps[ i ] ), nfmaps[ i ], cv::Size( width, height ) );
		}
		return nfmaps;
	}

	//
	Matrix normalizeMap( const Matrix &in )
	{
		// 0-1への正規化
		Matrix result( in.rows, in.cols );
		T minv, maxv;
		cv::minMaxLoc( in, &minv, &maxv );
		result = in.clone();
		result -= minv;
		result /= ( maxv - minv );
		return result;
	}
	
	//
	Matrix normalizeMapWithLocalMaxima( const Matrix &in )
	{
		// 最大値・極大値を考慮した正規化
		Matrix result = normalizeMap( in );

		int numlocal = 0;
		T lmaxmean = 0;

		for( int y=0; y < in.rows - stepLocalMaxima; y += stepLocalMaxima )
		{
			for( int x = 0 ; x < in.cols - stepLocalMaxima ; x += stepLocalMaxima )
			{
				Matrix roi( in, cv::Rect( x, y, stepLocalMaxima, stepLocalMaxima ) );
				T minv, maxv;
				cv::minMaxLoc( roi, &minv, &maxv );
				if( maxv != 1.0 )
				{
					lmaxmean += maxv;
					++numlocal;
				}
			}
		}
		lmaxmean /= numlocal;
		result *= pow( 1.0 - lmaxmean, 2.0 );
		return result;
	}
};
