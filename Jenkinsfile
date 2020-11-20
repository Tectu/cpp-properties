pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
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
    }
}
