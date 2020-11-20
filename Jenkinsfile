pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                steps
                {
                    cmakeBuild(
                        buildDir: 'build',
                        buildType: 'debug',
                        generator: 'Unix Makefiles',
                        installation: 'InSearchPath'
                    )
                }
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}
