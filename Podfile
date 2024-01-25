source 'https://cdn.cocoapods.org/'

platform :ios, '13.0'
inhibit_all_warnings! # 忽略所有警告


post_install do |installer|
    installer.generated_projects.each do |project|
        project.targets.each do |target|
            target.build_configurations.each do |config|
                config.build_settings['IPHONEOS_DEPLOYMENT_TARGET'] = '13.0'
            end
        end
    end
end


target 'MyApplication' do
	use_frameworks!
	pod 'AFNetworking', '~> 4.0'
	pod 'Masonry', '~> 1.1.0'
	pod 'FLAnimatedImage', '~> 1.0'
	pod 'SDWebImage', '~> 5.0'
  pod 'JXCategoryView'
end
