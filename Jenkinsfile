pipeline {
    agent any

    stages {
        stage('Run cmake')
        {
            steps
            {
                cmakeBuild(
                    buildDir: 'build',
                    cleanBuild: true,
                    generator: 'Unix Makefiles',
                    installation: 'InSearchPath'
                )
            }
        }

        stage('Build')
        {
            steps
            {
                dir('build') {
                    sh 'make -j4'
                }
            }
        }
    }
}

